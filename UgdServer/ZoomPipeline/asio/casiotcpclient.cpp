#include "casiotcpclient.h"
#include <QDebug>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

static QMutex s_uuid_mutex;
quint64 CAsioTcpClient::m_sUuid = 0;
CAsioTcpClient::CAsioTcpClient(size_t buffer_size, QObject *parent)
    : CAsioTcpSocket(buffer_size, parent), m_con_state(0)
    , dispatcher_(boost::bind(&CAsioTcpClient::onUnknownMessage, this, _1, _2))
    , codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_, _1, _2))
{
    connect(this, &CAsioTcpSocket::connected,this, &CAsioTcpClient::slot_clientConnected, Qt::QueuedConnection);
    connect(this, &CAsioTcpSocket::stateChange,this,&CAsioTcpClient::slot_clientStateChanged, Qt::QueuedConnection);
    connect(this, &CAsioTcpSocket::sentReadData,this, &CAsioTcpClient::slot_newDataRecieved, Qt::QueuedConnection);
    connect(this, &CAsioTcpSocket::disConnected,this,&CAsioTcpClient::slot_clientClosed, Qt::QueuedConnection);
    connect(this, &CAsioTcpSocket::erroString,this,&CAsioTcpClient::slot_displayError, Qt::QueuedConnection);
    connect(this, &CAsioTcpSocket::bytesWritten, this, &CAsioTcpClient::slot_someDataSent, Qt::QueuedConnection);
    s_uuid_mutex.lock();
    m_sUuid++;
    s_uuid_mutex.unlock();
    m_uuid = m_sUuid;

    m_device_id[0] = 0x49;
    m_device_id[1] = 0xFF & (m_uuid >> 40);
    m_device_id[2] = 0xFF & (m_uuid >> 32);
    m_device_id[3] = 0xFF & (m_uuid >> 24);
    m_device_id[4] = 0xFF & (m_uuid >> 16);
    m_device_id[5] = 0xFF & (m_uuid >> 8);
    m_device_id[6] = 0xFF & m_uuid;
    m_downlink_msn = 0;

}
CAsioTcpClient::~CAsioTcpClient()
{
    disconnect(this, &CAsioTcpSocket::connected,this, &CAsioTcpClient::slot_clientConnected);
    disconnect(this, &CAsioTcpSocket::stateChange,this,&CAsioTcpClient::slot_clientStateChanged);
    disconnect(this, &CAsioTcpSocket::sentReadData,this, &CAsioTcpClient::slot_newDataRecieved);
    disconnect(this, &CAsioTcpSocket::disConnected,this,&CAsioTcpClient::slot_clientClosed);
    disconnect(this, &CAsioTcpSocket::erroString,this,&CAsioTcpClient::slot_displayError);
    disconnect(this, &CAsioTcpSocket::bytesWritten, this, &CAsioTcpClient::slot_someDataSent);
}

void CAsioTcpClient::start(const QString &sIp, quint16 nPort)
{
    if(m_con_state)
        return;
    init();
    connectToHost(sIp, nPort);
}

void CAsioTcpClient::stop()
{
    disconnectFromHost();
    m_con_state = 0;
}

void CAsioTcpClient::slot_clientConnected()
{
    //qDebug() << __FUNCTION__ << __LINE__;
    m_con_state = 1;
}

void CAsioTcpClient::slot_clientStateChanged(int state)
{//qDebug() << __FUNCTION__ << __LINE__ << state;
    if(state == ConnectedState)
        m_con_state = 1;
    else
        m_con_state = 0;
}

void CAsioTcpClient::slot_newDataRecieved(const QByteArray & data)
{
    qDebug() << "client rx:" << data.size();
    CAsioTcpSocket * sock_client = qobject_cast<CAsioTcpSocket*>(sender());
    QByteArray ba(data);
    //sock_client->write(ba);
}

void CAsioTcpClient::slot_clientClosed()
{
    CAsioTcpSocket * sock_client = qobject_cast<CAsioTcpSocket*>(sender());
    qDebug() << "client close:" << sock_client;
}

void CAsioTcpClient::slot_displayError(const QString & erro)
{
    qDebug() << "client err:" << erro;
}

void CAsioTcpClient::slot_someDataSent(qint64 bytes)
{
    qDebug() << "client tx:" <<  bytes;
}

void CAsioTcpClient::sendHeartbeat()
{
#ifdef USE_PROTOBUF
    Heartbeat heartbeat;
    heartbeat.set_id(m_uuid);
    heartbeat.set_timestamp(QDateTime::currentSecsSinceEpoch());
    codec_.send(shared_from_this(), heartbeat);
#else
    uint8_t data[16];
    data[0] = 0xE7;
    //Message Function ID
    data[1] = 0xFF & (0x0002 >> 8);
    data[2] = 0xFF & 0x0002;
    data[3] = 0;
    data[4] = 16;
    //Message Properties

    //Device ID
    for(int i=0; i<7; i++)
        data[5+i] = m_device_id[i];
    //Message serial number
    data[12] = 0xFF & (m_downlink_msn >> 8);
    data[13] = 0xFF & m_downlink_msn;
    data[14] = frame_xor(&data[1], 13);

    data[15] = 0xE7;

    sendData((const char*)data, 16);
    m_downlink_msn++;
#endif
}

uint16_t CAsioTcpClient::frame_escape(uint8_t *ptr,uint16_t len)
{
    uint8_t *data = (uint8_t*)malloc(1024);
    if(data == NULL)
        return 0;
    uint16_t pos = 0;
    data[pos++] = ptr[0];
    for(int i=1; i<len-1; i++)
    {
        if(ptr[i] == 0xE7)
        {
            data[pos++] = 0xE6;
            data[pos++] = 0x02;
        }
        else if(ptr[i] == 0xE6)
        {
            data[pos++] = 0xE6;
            data[pos++] = 0x01;
        }
        else
            data[pos++] = ptr[i];
    }
    data[pos++] = ptr[len-1];
    memcpy(ptr,data,pos);
    free(data);
    return pos;
}

uint8_t CAsioTcpClient::frame_xor(uint8_t *ptr,uint16_t len)
{
    uint8_t res = ptr[0];
    for(int i=0; i<len; i++)
        res ^= ptr[i];
    return res;
}

void CAsioTcpClient::queryDefaultVersion()
{
#ifdef USE_PROTOBUF
    Query query;
    query.set_id(m_uuid);
    query.set_timestamp(QDateTime::currentSecsSinceEpoch());
    query.set_query_code(QueryDefaultVersion);
    QJsonDocument sendJson;
    QJsonObject jsonObj;
    jsonObj["ProductName"] = "ZH510";
    jsonObj["FileType"] = "CRC";
    jsonObj["FileSubType"] = "";
    jsonObj["Custom"] = "STD";
    sendJson.setObject(jsonObj);
    query.set_json_body(sendJson.toJson(QJsonDocument::Indented).data());
    codec_.send(shared_from_this(), query);
#else
    uint8_t data[1024] = {0};
    data[0] = 0xE7;
    //Message Function ID
    data[1] = 0xFF & (0x0003 >> 8);
    data[2] = 0xFF & 0x0003;
    data[3] = 0;
    data[4] = 16;
    //Message Properties

    //Device ID
    for(int i=0; i<7; i++)
        data[5+i] = m_device_id[i];
    //Message serial number
    data[12] = 0xFF & (m_downlink_msn >> 8);
    data[13] = 0xFF & m_downlink_msn;

    QJsonDocument sendJson;
    QJsonObject jsonObj;
    QJsonObject dataObj;
    jsonObj["RequestCode"] = 24;
    dataObj["ProductName"] = "ZH510";
    dataObj["FileType"] = "CRC";
    dataObj["FileSubType"] = "";
    dataObj["Custom"] = "STD";
    jsonObj["data"] = dataObj;
    sendJson.setObject(jsonObj);


    int json_len = strlen(sendJson.toJson(QJsonDocument::Indented).data());
    memcpy(&data[14], sendJson.toJson(QJsonDocument::Indented).data(), json_len);
    json_len += 1 + 14 + 2;
    data[3] = 0xFF & (json_len >> 8);
    data[4] = 0xFF & json_len;

    data[json_len-2] = frame_xor(&data[1],json_len-3); //check

    data[json_len-1] = 0xE7;
    json_len = frame_escape(data,json_len);//???


    sendData((const char*)data, json_len);
    m_downlink_msn++;
#endif
}

void CAsioTcpClient::onUnknownMessage(const TcpSocketPtr& conn,const MessagePtr& message)
{
    qDebug() << "onUnknownMessage: " << message->GetTypeName().c_str();
    conn->disconnectFromHost();
}

void CAsioTcpClient::onHeartBeat(const TcpSocketPtr& conn, const HeartbeatPtr& heartbeat)
{
    qDebug() << __FUNCTION__ << __LINE__ << heartbeat->timestamp();
}
