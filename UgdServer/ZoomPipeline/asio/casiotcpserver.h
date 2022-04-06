#ifndef CASIOTCPSERVER_H
#define CASIOTCPSERVER_H

#include "ioserviceclass.h"
#include "csocketsession.h"
#include "casiotcpsocket.h"
#include "boost/shared_ptr.hpp"

using boost::asio::ip::tcp;
class CAsioListen;
class CAsioTcpServer :
        public QObject,
        public boost::enable_shared_from_this<CAsioTcpServer>
{
    Q_OBJECT
public:
    explicit CAsioTcpServer(size_t socket_buffer = 4096,QObject *parent = nullptr);
    ~CAsioTcpServer();
    void init();
    virtual void incomingConnection(session_ptr session);

Q_SIGNALS:
    void newConnection(CAsioTcpSocket * socket);

    void deleteAllLink();
    void evt_NewClientArrived(session_ptr session);
public :
    bool listen(const QString & ip,qint16 port);
     void close();


    void setSocketOption(CTcpAbstractSocket::SocketOption option, uint value) {
        setSocketOption(option,false,value);
    }
    void setSocketOption(CTcpAbstractSocket::SocketOption option, bool isEnble) {
        setSocketOption(option,isEnble,0);
    }

    void setSocketOption(CTcpAbstractSocket::SocketOption option, bool isEnble, uint value);

    int setThreadSize(size_t size);
protected:

private:
    IOServiceClass m_io_svr;
    boost::shared_ptr<CAsioListen> m_listen;
    size_t m_buffer_size;
};

#endif // CASIOTCPSERVER_H
