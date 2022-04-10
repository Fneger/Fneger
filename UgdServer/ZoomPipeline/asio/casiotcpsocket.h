#ifndef CASIOTCPSOCKET_H
#define CASIOTCPSOCKET_H

#include "ctcpabstractsocket.h"
#include "csocketsession.h"


class IOServiceClass;
class CAsioTcpSocket;
typedef boost::weak_ptr<CAsioTcpSocket> TcpSocketWkPtr;
typedef boost::shared_ptr<CAsioTcpSocket> TcpSocketPtr;
class CAsioTcpSocket:
        public CTcpAbstractSocket,
        public boost::enable_shared_from_this<CAsioTcpSocket>,
        public boost::asio::noncopyable
{
    Q_OBJECT
public:
    explicit CAsioTcpSocket(size_t size = 4096,QObject *parent = nullptr);
    CAsioTcpSocket(session_ptr ses);
    ~CAsioTcpSocket();
    void init();
    void setSession(session_ptr ses);

Q_SIGNALS:

public Q_SLOTS:
    void connectToHost(const QString &hostName, quint16 port);

    void disconnectFromHost();

    void do_start();

    int resizeClientBackThreadSize(int size);
    inline void setIsNewClient(bool bIsNew) { isNewClient_ = bIsNew; }
    inline bool isNewClient() const { return isNewClient_; }
    inline qint64 activeTime() const { return activeTime_; }
    void updateActiveTime();
    inline void setActiveTime(qint64 nTime) { activeTime_ = nTime; }
    void sendData(const char * data, int size);
protected:
    virtual void hostConnected1();

private:
    bool serverBuild_;
    session_ptr clientSsession_;
    session_ptr con_;
    session_ptr session_;
    static boost::shared_ptr<IOServiceClass> s_ioserver_;
    static volatile ulong s_linkCout_;
    bool isNewClient_;
    qint64 activeTime_;
};

#endif // CASIOTCPSOCKET_H
