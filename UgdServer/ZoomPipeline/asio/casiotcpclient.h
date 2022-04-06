#ifndef CASIOTCPCLIENT_H
#define CASIOTCPCLIENT_H

#include "casiotcpsocket.h"
#include "ccodec.h"
#include "dispatcher.h"
#include "protobuf_message.pb.h"

using namespace fneger;

typedef boost::shared_ptr<Heartbeat> HeartbeatPtr;

class CAsioTcpClient : public CAsioTcpSocket
{
    Q_OBJECT
public:
    explicit CAsioTcpClient(size_t buffer_size, QObject *parent = nullptr);
    ~CAsioTcpClient();
    void start(const QString &sIp, quint16 nPort);
    void stop();
    inline int getConState() const { return m_con_state; }
    inline quint64 uuid() const { return m_uuid; }
    const uint8_t *deviceId() const  { return  m_device_id; }
    void sendHeartbeat();
    void queryDefaultVersion();
    void onUnknownMessage(const TcpSocketPtr& conn,const MessagePtr& message);
    void onHeartBeat(const TcpSocketPtr& conn,const HeartbeatPtr& heartbeat);

Q_SIGNALS:

public Q_SLOTS:
    void slot_clientConnected();
    void slot_clientStateChanged(int state);
    void slot_newDataRecieved(const QByteArray & data);
    void slot_clientClosed();
    void slot_displayError(const QString & erro);
    void slot_someDataSent(qint64 bytes);

private:
    uint16_t frame_escape(uint8_t *ptr,uint16_t len);
    uint8_t frame_xor(uint8_t *ptr,uint16_t len);

private:
    int m_con_state;
    quint64 m_uuid;
    static quint64 m_sUuid;
    quint16 m_downlink_msn;
    uint8_t m_device_id[7];
    Q_DISABLE_COPY(CAsioTcpClient)
    ProtobufDispatcher dispatcher_;
    ProtobufCodec codec_;
};

#endif // CASIOTCPCLIENT_H
