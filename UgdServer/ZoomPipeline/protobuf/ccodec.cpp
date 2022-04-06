#include "ccodec.h"
#include "google-inl.h"
#include <google/protobuf/descriptor.h>
#include <QDebug>
#include "zlib.h"  // adler32
#include "Endian.h"


void ProtobufCodec::fillEmptyBuffer(CBuffer* buf, const google::protobuf::Message& message)
{
    buf->clear();
    // buf->retrieveAll();
    assert(buf->readableBytes() == 0);
    buf->hasWritten(kHeaderLen);
    const std::string& typeName = message.GetTypeName();
    int32_t nameLen = static_cast<int32_t>(typeName.size()+1);
    buf->appendInt32(nameLen);
    buf->append(typeName.c_str(), nameLen);
    // code copied from MessageLite::SerializeToArray() and MessageLite::SerializePartialToArray().
    GOOGLE_DCHECK(message.IsInitialized()) << InitializationErrorMessage("serialize", message);

    /**
    * 'ByteSize()' of message is deprecated in Protocol Buffers v3.4.0 firstly.
    * But, till to v3.11.0, it just getting start to be marked by '__attribute__((deprecated()))'.
    * So, here, v3.9.2 is selected as maximum version using 'ByteSize()' to avoid
    * potential effect for previous muduo code/projects as far as possible.
    * Note: All information above just INFER from
    * 1) https://github.com/protocolbuffers/protobuf/releases/tag/v3.4.0
    * 2) MACRO in file 'include/google/protobuf/port_def.inc'.
    * eg. '#define PROTOBUF_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))'.
    * In addition, usage of 'ToIntSize()' comes from Impl of ByteSize() in new version's Protocol Buffers.
    */

    int byte_size = google::protobuf::internal::ToIntSize(message.ByteSizeLong());
    buf->ensureWritableBytes(byte_size);

    uint8_t* start = (uint8_t*)buf->beginWrite();
    uint8_t* end = message.SerializeWithCachedSizesToArray(start);
    if (end - start != byte_size)
    {
    ByteSizeConsistencyError(byte_size, google::protobuf::internal::ToIntSize(message.ByteSizeLong()), static_cast<int>(end - start));
    }
    buf->hasWritten(byte_size);
    int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(buf->readableBytes() +kCheckSumLen));
    buf->prepend(&len, sizeof len);

    int32_t checkSum = static_cast<int32_t>(
    ::adler32(1,
            reinterpret_cast<const Bytef*>(buf->peek()),
            static_cast<uint>(buf->readableBytes())));
    buf->appendInt32(checkSum);
    assert(buf->readableBytes() == sizeof nameLen + nameLen + byte_size + sizeof checkSum);
    //buf->printData();

}

//
// no more google code after this
//

//
// FIXME: merge with RpcCodec
//

namespace
{
    const std::string kNoErrorStr = "NoError";
    const std::string kInvalidLengthStr = "InvalidLength";
    const std::string kCheckSumErrorStr = "CheckSumError";
    const std::string kInvalidNameLenStr = "InvalidNameLen";
    const std::string kUnknownMessageTypeStr = "UnknownMessageType";
    const std::string kParseErrorStr = "ParseError";
    const std::string kUnknownErrorStr = "UnknownError";
}

const std::string& ProtobufCodec::errorCodeToString(ErrorCode errorCode)
{
    switch (errorCode)
    {
    case kNoError:
        return kNoErrorStr;
    case kInvalidLength:
        return kInvalidLengthStr;
    case kCheckSumError:
        return kCheckSumErrorStr;
    case kInvalidNameLen:
        return kInvalidNameLenStr;
    case kUnknownMessageType:
        return kUnknownMessageTypeStr;
    case kParseError:
        return kParseErrorStr;
    default:
        return kUnknownErrorStr;
    }
}

void ProtobufCodec::defaultErrorCallback(const TcpSocketPtr& conn,
                                         CBuffer *buf,
                                         ErrorCode errorCode)
{
    qWarning() << "ProtobufCodec::defaultErrorCallback - " << QString::fromStdString(errorCodeToString(errorCode));
    if (conn && conn->state() == CAsioTcpSocket::ConnectedState)
    {
        conn->disconnectFromHost();
    }
}

int32_t asInt32(const char* buf)
{
    int32_t be32 = 0;
    ::memcpy(&be32, buf, sizeof(be32));
    return sockets::networkToHost32(be32);
}

void ProtobufCodec::onMessage(const TcpSocketPtr& conn,
                              CBuffer *buf)
{
    //buf->printData();
    while (buf->readableBytes() >= kMinMessageLen + kHeaderLen)
    {
        const int32_t len = buf->peekInt32();
        if (len > kMaxMessageLen || len < kMinMessageLen) //非法数据包,直接丢弃
        {
            errorCallback_(conn, buf, kInvalidLength);
            buf->clear();
            break;
        }
        else if (buf->readableBytes() >= google::protobuf::implicit_cast<size_t>(len))
        {
            ErrorCode errorCode = kNoError;
            MessagePtr message = parse(buf->peek(), len, &errorCode);
            if (errorCode == kNoError && message)
            {
                messageCallback_(conn, message);
                buf->retrieve(len);
            }
            else //解析失败，丢弃该数据包
            {
                errorCallback_(conn, buf, errorCode);
                buf->retrieve(len);
            }
        }
        else //可能数据包未接收完
        {
            break;
        }
    }
}

google::protobuf::Message* ProtobufCodec::createMessage(const std::string& typeName)
{
    google::protobuf::Message* message = NULL;
    const google::protobuf::Descriptor* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
    if (descriptor)
    {
        const google::protobuf::Message* prototype =
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (prototype)
        {
            message = prototype->New();
        }
    }
    return message;
}

MessagePtr ProtobufCodec::parse(const char* buf, int len, ErrorCode* error)
{
    MessagePtr message;

    // check sum
    int32_t expectedCheckSum = asInt32(buf + len - kCheckSumLen);
    int32_t checkSum = static_cast<int32_t>(
      ::adler32(1,
                reinterpret_cast<const Bytef*>(buf),
                static_cast<uint>(len - kCheckSumLen)));

    //CBuffer::printData((uint8_t*)buf, len);
    if (checkSum == expectedCheckSum)
    {
    // get message type name
    int32_t nameLen = asInt32(buf + kHeaderLen);
    if (nameLen >= 2 && nameLen <= len - kHeaderLen - kTypeNameLen - kCheckSumLen)
    {
        std::string typeName(buf + kHeaderLen + kTypeNameLen, buf + kHeaderLen + kTypeNameLen + nameLen - 1);
        // create message object
        message.reset(createMessage(typeName));
        if (message)
        {
            // parse from buffer
            const char* data = buf + kHeaderLen + kTypeNameLen + nameLen;
            int32_t dataLen = len - nameLen - kHeaderLen - kTypeNameLen - kCheckSumLen;
            if (message->ParseFromArray(data, dataLen))
            {
                *error = kNoError;
            }
            else
            {
                *error = kParseError;
            }
        }
        else
        {
            *error = kUnknownMessageType;
        }
        }
        else
        {
            *error = kInvalidNameLen;
        }
    }
    else
    {
        *error = kCheckSumError;
    }

    return message;
}
