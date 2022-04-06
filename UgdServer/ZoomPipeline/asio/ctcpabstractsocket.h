#ifndef CTCPABSTRACTSOCKET_H
#define CTCPABSTRACTSOCKET_H

#include <QObject>
#include <QDebug>


class CTcpAbstractSocket : public QObject
{
    Q_OBJECT
public:
    enum SocketState {
        UnconnectedState = 0,
        HostFinding = 1,
        SSLHandshakeing = 3,
        ConnectingState = 2,
        ConnectedState = 4
    };

    enum SocketOption {
        Multicast_Loopback, //QAbstractSocket::MulticastLoopbackOption (bool)
        Multicast_TTL, //QAbstractSocket::MulticastTtlOption, IP_MULTICAST_TTL  (int)
        IP_TCP_NODelay, //QAbstractSocket::LowDelayOption (bool)
        Broadcast, //SO_BROADCAST (bool)
        Linger, //SO_LINGER (bool,int)
        Keep_Live,//QAbstractSocket::KeepAliveOption, SO_KEEPALIVE (bool)
        Receive_Buffer_Size, //QAbstractSocket::ReceiveBufferSizeSocketOption (int)
        Receive_Low_Watermark, //SO_RCVLOWAT (int)
        Reuse_Address, //SO_REUSEADDR (bool)
        Send_Buffer_Size,//QAbstractSocket::SendBufferSizeSocketOption (int)
        Send_Low_Watermark //SO_SNDLOWAT (int)
    };
    explicit CTcpAbstractSocket(QObject *parent = nullptr);
    virtual ~CTcpAbstractSocket(){}

Q_SIGNALS:
    void connected();
    void disConnected();
    void stateChange(int);
    void sentReadData(const QByteArray & data);
    void erroString(const QString & erro);
    void hostFinded();
    void bytesWritten(qint64 bytes);

public Q_SLOTS:

    virtual void connectToHost(const QString &hostName, quint16 port) = 0;

    virtual void disconnectFromHost() = 0;

    inline void write(const QByteArray & data){
        sendData(data.data(),data.size());
    }

    inline void write(const char * data, int size = -1){
        sendData(data,size);
    }
#if 0
    virtual void setSocketOption(CTcpAbstractSocket::SocketOption option, bool isEnble, uint value) = 0;

    virtual std::pair<bool,int> getSocketOption(CTcpAbstractSocket::SocketOption) = 0;


    void setSocketOption(CTcpAbstractSocket::SocketOption option,bool isEnble) {
        setSocketOption(option,isEnble,0);
    }
    void setSocketOption(CTcpAbstractSocket::SocketOption option,uint value) {
        setSocketOption(option,false,value);
    }
#endif
public :
    int socketDescriptor() const {return handle;}

    int errorCode() const {return erro_code;}
    QString erro() const {return erro_string;}

    SocketState state() const {return state_;}

    QString peerIp() const {return peerIp_;}
    qint16 peerPort() const  {return peerPort_; }
    void hostConnected(int handle_id, const std::string &ip, uint16_t prot);
    void haveErro(int erro_code,const std::string & erro_string);
protected:
    virtual void sendData(const char * data, int size) = 0;

    virtual void haveErro();
    virtual void hostConnected1();
    virtual bool readDataed(const char * data,std::size_t bytes_transferred);
    virtual bool writeDataed(std::size_t bytes_transferred,std::size_t willWriteSize);
    virtual void finedHosted();
    virtual void heartTimeOut(int /*timeout*/){}
    virtual void handshaked(){}
    inline void setState(SocketState st) {this->state_ = st;}
    inline void setSocketPtr(int soc) {handle = soc;}
private :
    volatile int handle = -1;
    QString erro_string;
    int erro_code = 0;
    volatile SocketState state_ = UnconnectedState;
    QString peerIp_;
    qint16 peerPort_;

    friend class CSocketSession;
    Q_DISABLE_COPY(CTcpAbstractSocket)
};

#endif // CTCPABSTRACTSOCKET_H
