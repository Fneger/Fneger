#include "cbuffer.h"
#include <QDebug>

CBuffer::CBuffer(size_t nSize)
    : writeIdx_(0)
    , readIdx_(0)
{
    buffer_.resize(nSize);
	memset(buffer_.data(), 0, nSize);
}

CBuffer::~CBuffer()
{

}

size_t CBuffer::append(const void *buf, size_t bufLen)
{
    if(writableBytes() < bufLen)
    {
        qDebug("Buffer not enough space,reallocate memory!\n");
		if (bufLen > S_BUFFER_MAX_SIZE)
			return 0;
        ensureWritableBytes(bufLen);
    }
    char *pStart = buffer_.data();
    char *pBufStart = (char*)buf;
    memcpy(pStart + writeIdx_, pBufStart, bufLen);
    writeIdx_ += bufLen;
    return bufLen;
}

size_t CBuffer::read(void *buf, size_t buflen)
{
    if(readableBytes() < buflen)
    {
        qDebug("[RTSP] Buffer data illegal\n");
        return 0;
    }

    char *pStart = buffer_.data();
    char *pBufStart = (char*)buf;
    if(buf != nullptr)
        memcpy(pBufStart, pStart + readIdx_, buflen);
    readIdx_ += buflen;
    return buflen;
}

void CBuffer::clear()
{
    memset(buffer_.data(), 0, buffer_.size());
    writeIdx_ = 0;
    readIdx_ = 0;
}

void CBuffer::ensureWritableBytes(size_t len)
{
	assert(len <= S_BUFFER_MAX_SIZE);
    if (writableBytes() < len)
    {
        if(readableBytes() > 0)
        {
            std::vector<char> buf(readableBytes());
            memcpy(buf.data(), beginRead(), readableBytes());
            buffer_.resize(len + readableBytes());
            memcpy(buffer_.data(), buf.data(), readableBytes());
            readIdx_ = 0;
            writeIdx_ = buf.size();
        }
        else
        {
            buffer_.resize(len);
            readIdx_ = 0;
            writeIdx_ = 0;
        }
    }
    assert(writableBytes() >= len);
}

void CBuffer::printData()
{
    QString dbgMsg;
    char *pData = buffer_.data();
    for(size_t i = 0; i < writeIdx_; ++i)
        dbgMsg += QString("%1 ").arg((uint8_t)pData[i], 2, 16, QChar('0'));
    qDebug() << dbgMsg;
}

void CBuffer::printData(uint8_t *pData, int nLen)
{
    QString dbgMsg;
    for(size_t i = 0; i < nLen; ++i)
        dbgMsg += QString("%1 ").arg((uint8_t)pData[i], 2, 16, QChar('0'));
    qDebug() << dbgMsg;
}
