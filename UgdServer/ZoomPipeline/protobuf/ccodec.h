#ifndef CCODEC_H
#define CCODEC_H

#include <google/protobuf/message.h>
#include "boost/noncopyable.hpp"
#include "casiotcpsocket.h"
#include "cbuffer.h"

// struct ProtobufTransportFormat __attribute__ ((__packed__))
// {
//   int32_t  len; //all field length
//   int32_t  nameLen;
//   char     typeName[nameLen];
//   char     protobufData[len-nameLen-8];
//   int32_t  checkSum; // adler32 of len, nameLen, typeName and protobufData
// }

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufCodec : public boost::noncopyable
{
public:
    enum ErrorCode
    {
      kNoError = 0,
      kInvalidLength,
      kCheckSumError,
      kInvalidNameLen,
      kUnknownMessageType,
      kParseError,
    };

    typedef boost::function<void (const TcpSocketPtr&,
                                  const MessagePtr&)> ProtobufMessageCallback;

    typedef boost::function<void (const TcpSocketPtr&,
                                  CBuffer*,
                                  ErrorCode)> ErrorCallback;
    explicit ProtobufCodec(const ProtobufMessageCallback& messageCb)
      : messageCallback_(messageCb),
        errorCallback_(defaultErrorCallback)
    {
    }

    ProtobufCodec(const ProtobufMessageCallback& messageCb, const ErrorCallback& errorCb)
      : messageCallback_(messageCb),
        errorCallback_(errorCb)
    {
    }

    //返回未解析字节
    void onMessage(const TcpSocketPtr& conn,
                   CBuffer* buf);

    void send(const TcpSocketPtr& conn,
              const google::protobuf::Message& message)
    {
      // FIXME: serialize to TcpConnection::outputBuffer()
      CBuffer buf;
      fillEmptyBuffer(&buf, message);
      if(conn != nullptr)
        conn->sendData(buf.data(), buf.readableBytes());
    }

    static const std::string& errorCodeToString(ErrorCode errorCode);
    static void fillEmptyBuffer(CBuffer *buf, const google::protobuf::Message& message);
    static google::protobuf::Message* createMessage(const std::string& type_name);
    static MessagePtr parse(const char* buf, int len, ErrorCode* errorCode);

   private:
    static void defaultErrorCallback(const TcpSocketPtr&,
                                     CBuffer*,
                                     ErrorCode);

    ProtobufMessageCallback messageCallback_;
    ErrorCallback errorCallback_;

    const static int kHeaderLen = sizeof(int32_t);
    const static int kCheckSumLen = sizeof(int32_t);
    const static int kTypeNameLen = sizeof(int32_t);
    const static int kMinMessageLen = kHeaderLen + kCheckSumLen + kTypeNameLen; // nameLen + typeName + checkSum
    const static int kMaxMessageLen = 64*1024*1024; // same as codec_stream.h kDefaultTotalBytesLimit
};

#endif // CCODEC_H
