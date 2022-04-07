#ifndef CBUFFER_H
#define CBUFFER_H

#include "boost/noncopyable.hpp"
#include "boost/thread.hpp"
#include <vector>
#include "Endian.h"
#include <QDebug>

class CBuffer
{
public:
    explicit CBuffer(size_t nSize = 1024);
    virtual ~CBuffer();

    size_t append(const void *buf, size_t bufLen);
    size_t read(void *buf, size_t buflen);
    void clear();
    void resize(size_t nSize)
    {
        buffer_.resize(nSize);
        writeIdx_ = 0;
        readIdx_ = 0;
    }
    const char *data(){ return buffer_.data(); }

    size_t readableBytes() const
    { return writeIdx_ - readIdx_; }

    size_t writableBytes() const
    { return buffer_.size() - writeIdx_; }

    const char* beginWrite() const
    { return buffer_.data() + writeIdx_; }

    char* beginRead()
    {
        return buffer_.data() + readIdx_;
    }

    void ensureWritableBytes(size_t len);

    void hasWritten(size_t len)
    {
      assert(len <= writableBytes());
      writeIdx_ += len;
    }

    const char* peek() const
    { return buffer_.data() + readIdx_; }

    ///
    /// Append int64_t using network endian
    ///
    void appendInt64(int64_t x)
    {
      int64_t be64 = sockets::hostToNetwork64(x);
      append(&be64, sizeof be64);
    }

    ///
    /// Append int32_t using network endian
    ///
    void appendInt32(int32_t x)
    {
      int32_t be32 = sockets::hostToNetwork32(x);
      append(&be32, sizeof be32);
    }

    void appendInt16(int16_t x)
    {
      int16_t be16 = sockets::hostToNetwork16(x);
      append(&be16, sizeof be16);
    }

    void appendInt8(int8_t x)
    {
      append(&x, sizeof x);
    }

    ///
    /// Read int64_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int64_t readInt64()
    {
      int64_t result = peekInt64();
      readIdx_ += 8;
      return result;
    }

    ///
    /// Read int32_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int32_t readInt32()
    {
      int32_t result = peekInt32();
      readIdx_ += 4;
      return result;
    }

    int16_t readInt16()
    {
      int16_t result = peekInt16();
      readIdx_ += 2;
      return result;
    }

    int8_t readInt8()
    {
      int8_t result = peekInt8();
      readIdx_ += 1;
      return result;
    }

    ///
    /// Peek int64_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int64_t)
    int64_t peekInt64() const
    {
      assert(readableBytes() >= sizeof(int64_t));
      int64_t be64 = 0;
      ::memcpy(&be64, peek(), sizeof be64);
      return sockets::networkToHost64(be64);
    }

    ///
    /// Peek int32_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int32_t peekInt32() const
    {
      assert(readableBytes() >= sizeof(int32_t));
      int32_t be32 = 0;
      ::memcpy(&be32, peek(), sizeof be32);
      return sockets::networkToHost32(be32);
    }

    static int32_t peekInt32(char *pData, size_t nLen)
    {
      if(nLen < sizeof(int32_t))
          return 0;
      int32_t be32 = 0;
      ::memcpy(&be32, pData, sizeof be32);
      return sockets::networkToHost32(be32);
    }

    int16_t peekInt16() const
    {
      assert(readableBytes() >= sizeof(int16_t));
      int16_t be16 = 0;
      ::memcpy(&be16, peek(), sizeof be16);
      return sockets::networkToHost16(be16);
    }

    int8_t peekInt8() const
    {
      assert(readableBytes() >= sizeof(int8_t));
      int8_t x = *peek();
      return x;
    }

    ///
    /// Prepend int64_t using network endian
    ///
    void prependInt64(int64_t x)
    {
      int64_t be64 = sockets::hostToNetwork64(x);
      prepend(&be64, sizeof be64);
    }

    ///
    /// Prepend int32_t using network endian
    ///
    void prependInt32(int32_t x)
    {
      int32_t be32 = sockets::hostToNetwork32(x);
      prepend(&be32, sizeof be32);
    }

    void prependInt16(int16_t x)
    {
      int16_t be16 = sockets::hostToNetwork16(x);
      prepend(&be16, sizeof be16);
    }

    void prependInt8(int8_t x)
    {
      prepend(&x, sizeof x);
    }

    void prepend(const void* /*restrict*/ data, size_t len)
    {
      const char* d = static_cast<const char*>(data);
      memcpy(beginRead(), d, len);
    }

    void retrieve(size_t len)
    {
      assert(len <= readableBytes());
      readIdx_ += len;
    }

    void printData();
    static void printData(uint8_t *pData, int nLen);

	static const int S_BUFFER_MAX_SIZE = 10 * 1024 * 1024;

private:



private:
	
    std::vector<char> buffer_;
    volatile size_t writeIdx_;
    volatile size_t readIdx_;
};

#endif // CBUFFER_H
