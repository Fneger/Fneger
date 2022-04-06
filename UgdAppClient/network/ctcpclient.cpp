#include "ctcpclient.h"
#include "ssl_config.h"
#include <QMutex>
#include "st_message.h"
#include <QCoreApplication>
#include <QJsonObject>
#include <QElapsedTimer>
#include <QJsonArray>
#include <QDateTime>
#include <QTimer>
#include "ccommon.h"
#include "myautomutex.h"
#include <QThread>

//闂備緡鍓欓悘婵嬪储閵堝棙濯撮悹鎭掑妽閺嗗繐顫楅崟顒佲拹缁绢厼澧庨埀顒佺⊕椤ㄥ牓顢栨担鍦枖
#define NORMAL 0  			//濠殿喗绻愮徊浠嬫偉
#define TIME_OUT 1			//闁烩剝甯掗幊蹇擃渻
#define THREE_DUP_ACK 2		//3婵炴垶鎼╂禍顏堝闯閸涘﹤绶炵€光偓閻＄瓈

using namespace ExampleServer;
using namespace BdUgdServer;

static quint64 S_nRecBytes = 0; //闂佽浜介崕鏌ュ极瑜版帒绠戦悹鍥皺閹界喖鏌ら崫鍕偓褰掑汲
static quint64 S_nSentBytes = 0; //闂佸憡鐟﹂崹鍧楀焵椤戣法鍔嶉柍褜鍓濋褔鎮鸿閹崇偤宕掑☉娆愵啀
static QMutex S_mBytesRateMutex;

//闂佺绻堥崝宀勬儑椤掑嫬鐭楅柛灞剧⊕濞
static int MSS=768;//闂佸憡顨嗗ú鎴︽煂濠婂牆绠柕澶涢檮閻庮喗绻涢崼銏℃毈闁哄棜椴搁幆鏃堟偡濞嗗繐顏╅柣锝囧亾缁B
static int ssthresh=16*MSS;//闂侀€涚┒閸ㄥ綊骞嗘惔銊ョ闁靛ň鏅滈敍宀勬⒒閸曨垰绀嗘繝闈涙閸嬫捇姊荤壕瀣槹16

/**闂傚倸鎳庣换鎴濃攦閳ь剚鎱ㄩ幒鎴濃偓璇差啅閸忚偐顩茬憸蹇涘极閹捐绠柕澶堝労閺
    闁哄鏅滈弻銊ッ洪弽顓炵９
        0:闂佸搫鐗滄禍娆忊槈椤忓牆绀岄柛婊冨暟缁€澶岀磽閸愨晛鐏╃紒顔挎硾椤垽鏁愰崨顖氱厬
        1:闂備焦褰冪粔宕囨閸撲焦濯奸柍鈺佸暞椤ρ囨煕閿濆啫濮€缂佸鎸冲 				闁诲海鏁搁幊鎾惰姳閼碱剛椹抽柡宥庡亝濞堥梺閫涚┒閸ㄥ綊骞嗘惔銊ョ
        2:3婵炴垶鎼╂禍顏堝闯閸涘﹤绶炵€光偓閻＄瓈 婵炴垶姊婚崰搴＄暤閸℃稑鍙婃い鏍ㄧ瑜般儵姊洪銈呮灈闁革絽鎲＄€甸柣搴ｆ暩閹虫挾鑺遍懠顒傞┏闁哄稁鍋呭▓闂婎偄娴傞崑濠囧焵椤掑倸鏋戝ù鐙€鍠楀
*/
int isCrowd(int cwnd){
    int p=cwnd/MSS*2;//婵炲瓨绫傞崨顔芥闂佽鐏氶崕閬嶃€侀敐鍜佹健闁稿本绮岄懞鍐测槈閹惧墎娈 婵炴垶姊婚崰搴＄暤閸℃稑鍙婄紓浣瑰姈椤ㄥ懓銇愬☉娆忕窞鐟滃秹鎯0*100%
    if(rand()%101<p){//p%闂佹眹鍔岀€氼參銆呰閹娊宕惰缁叉椽鏌ｉ姀銏犳瀾閻庢哎鍨虹换
        if(rand()%101<50){//50%濠殿喗甯掗崐璇差啅閼测晜鎯ラ柛娑卞枟椤
            return TIME_OUT;
        }else{//50%濠殿喗甯掗崐璇差啅閸忓吋浜ら柡鍌涘缁€鈧婵炴垶鎼╂禍顏堝闯閸涘﹤绶炵€光偓閻＄瓈 婵炴垶姊婚崰搴＄暤閸℃稑鍙婃い鏍ㄧ瑜般儵姊洪銈呮灈闁革絽鎲＄€
            return THREE_DUP_ACK;
        }
    }else{
        return NORMAL;
    }
}

CTcpClient::CTcpClient(QObject *parent)
    : QObject(parent)
    , m_client(nullptr)
    , m_bIsConnected(false)
    , m_nAuthLevel(-1)
    , m_bWaittingAckStatus(AckReceived_E)
    , m_bIsStartTest(false)
    , m_heartbeatAckReturned(true)
{
    m_nPayload = DATA_PAYLOAD;
    m_bSsl = false;
    m_maxUUID = 2;
    m_minUUID = 0xffffffffffffffff;
    QString idStr = GetDeviceId();
    uint8_t bcdcode[8] = {0};
    uint16_t bcdpos = 0;
    int bcdlen = 0;
    str2bcd(&bcdcode[1],idStr.toLocal8Bit().data(),&bcdlen);
    m_uuid = get8bytes(bcdcode,&bcdpos);
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&CTcpClient::on_timerTimeout);
    m_timer->setInterval(100);
    resetCcp();
}

CTcpClient::~CTcpClient()
{
    stopClient();
    if(m_client != nullptr)
        m_client->deleteLater();
}

quint64 CTcpClient::uuid()
{
    return m_uuid;
}

void CTcpClient::setUuid(quint64 uuid)
{
    m_uuid = uuid;
    QString str = QString("%1").arg(uuid,16,16,QChar('0'));
    SetDeviceId(&str.toLocal8Bit().data()[3]);
}

void CTcpClient::setServerInfo(const QString &sIp, const quint16 nPort, const QString &userName, const QString &passwd)
{
    m_serverIp = sIp;
    m_serverPort = nPort;
    m_userName = userName;
    m_password = passwd;
}

void CTcpClient::startClient()
{
    stopClient();
    reConnect();
    m_timer->start();
}

void CTcpClient::stopClient()
{
    m_timer->stop();
    if(m_client != nullptr && m_bIsConnected)
        m_client->abort();
    if(m_client != nullptr)
    {
        m_client->deleteLater();
        m_client = nullptr;
    }
}


void CTcpClient::on_client_trasferred(qint64 dtw)
{
    if (dtw <= sizeof(BD_MSG_HEARTBEATING_S))
        return;
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
#if (ZP_WANTSSL!=0)
        QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(sender());
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());
        if (pSockSsl)
            displayMessage(QString("client %1 Transferrd %2 bytes.").arg(m_uuid,16,16,QChar('0')).arg(dtw));
        else if (pSockTcp)
            displayMessage(QString("client %1 Transferrd %2 bytes.").arg(m_uuid,16,16,QChar('0')).arg(dtw));
#else
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());
        if (pSockTcp)
            displayMessage(QString("client %1 Transferrd %2 bytes.").arg(m_uuid,16,16,QChar('0').arg(dtw));
#endif
    }
    updateSentBytes(dtw);
}
void CTcpClient::on_client_connected()
{
    if(sender() != m_client)
        return;
    m_bIsConnected = true;
#if (ZP_WANTSSL!=0)
    QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(sender());
    QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());

    if (pSockSsl)
    {
        displayMessage(QString("client %1 connected.").arg(m_uuid,16,16,QChar('0')));
        if(m_nAuthLevel >= 0)
            SendHeartbeatPacket();
        else
            login();
    }
    else if (pSockTcp)
    {
        displayMessage(QString("client %1 connected.").arg(m_uuid,16,16,QChar('0')));
        if(m_nAuthLevel >= 0)
            SendHeartbeatPacket();
        else
            login();
    }
#else
    QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());
    if (pSockTcp)
    {
        displayMessage(QString("client %1 connected.").arg(m_uuid,16,16,QChar('0')));
        if(m_bIsLogin)
            SendHeartbeatPacket();
        else
            Login();
    }
#endif
}
void CTcpClient::on_client_disconnected()
{
    if(sender() != m_client)
        return;
#if (ZP_WANTSSL!=0)
    QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(sender());
    QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());
    if (pSockSsl)
    {
        displayMessage(QString("client %1 disconnected.").arg(m_uuid,16,16,QChar('0')));
        //disconnect the signal immediately so that the system resource could be freed.
        disconnect(pSockSsl, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
        disconnect(pSockSsl, SIGNAL(encrypted()),this, SLOT(on_client_connected()));
        disconnect(pSockSsl, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
        disconnect(pSockSsl, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        disconnect(pSockSsl, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
        pSockSsl->deleteLater();
    }
    else if (pSockTcp)
    {
        displayMessage(QString("client %1 disconnected.").arg(m_uuid,16,16,QChar('0')));
        //disconnect the signal immediately so that the system resource could be freed.
        disconnect(pSockTcp, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
        disconnect(pSockTcp, SIGNAL(connected()),this, SLOT(on_client_connected()));
        disconnect(pSockTcp, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
        disconnect(pSockTcp, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        disconnect(pSockTcp, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
        pSockTcp->deleteLater();
    }
#else
    QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sender());
    if (pSockTcp)
    {
        displayMessage(QString("client %1 disconnected.").arg(m_uuid,16,16,QChar('0')));
        //disconnect the signal immediately so that the system resource could be freed.
        disconnect(pSockTcp, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
        disconnect(pSockTcp, SIGNAL(connected()),this, SLOT(on_client_connected()));
        disconnect(pSockTcp, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
        disconnect(pSockTcp, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        disconnect(pSockTcp, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
        pSockTcp->deleteLater();
    }
#endif
    if(m_client == pSockSsl || m_client == pSockTcp)
        m_client = nullptr;
    m_bIsConnected = false;
}
void CTcpClient::displayError(QAbstractSocket::SocketError)
{
    if(sender() != m_client)
        return;
    QTcpSocket * sock = qobject_cast<QTcpSocket *> (sender());
    if (sock)
    {
#if (ZP_WANTSSL!=0)
        QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(sock);
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sock);
        if (pSockSsl)
            displayMessage(QString("client %1 error msg:").arg(m_uuid,16,16,QChar('0'))+sock->errorString());
        else if (pSockTcp)
            displayMessage(QString("client %1 error msg:").arg(m_uuid,16,16,QChar('0'))+sock->errorString());
#else
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(sock);
        if (pSockTcp)
            displayMessage(QString("client %1 error msg:").arg(m_uuid,16,16,QChar('0'))+sock->errorString());
#endif
    }
    if(m_client != nullptr)
    {
        m_client->deleteLater();
        m_client = nullptr;
    }
}
void CTcpClient::new_data_recieved()
{
    if(sender() != m_client)
        return;
    QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
    if (pSock)
    {
        QByteArray array =pSock->readAll();
        updateRecBytes(array.size());
        if (array.size() <= sizeof(BD_MSG_HEARTBEATING_S))
            return;
        //in this example, we just do nothing but to display the byte size.
#if (ZP_WANTSSL!=0)
        QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(pSock);
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(pSock);
        if (pSockSsl)
            displayMessage(QString("client %1 Recieved %2 bytes.").arg(m_uuid,16,16,QChar('0')).arg(array.size()));
        else if (pSockTcp)
            displayMessage(QString("[%1]client %2 Recieved %3 bytes.").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(m_uuid,16,16,QChar('0')).arg(array.size()));
#else
        QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(pSock);
        if (pSockTcp)
            displayMessage(QString("client %1 Recieved %1 bytes.").arg(m_uuid,16,16,QChar('0')).arg(array.size()));
#endif
        m_receivedBlock.append(array);
        uint8_t *bufptr = (uint8_t*)m_receivedBlock.data();
        uint16_t buflen = m_receivedBlock.size();
        int retlen, valid_len;
        uint8_t *data = NULL;
        retlen = 0;
        bool finded = false;
        int pos = 0;
        for(int i=0; i<buflen; i++)
        {
            if(bufptr[i] == 0xE7 && finded == false)//闂佺懓鐏氶崕鎶藉春瀹€鍕瀬闁绘鐗嗙粊锕傛煕閺嵮勫櫣缂佽鲸鍨堕幈銊р偓锝庡亞閸ㄥジ鐓
            {
                pos = i;
                finded = true;
            }
            else if(bufptr[i] == 0xE7 && finded == true) //闂佺懓鐏氶崕鎶藉春瀹€鍕瀬闁绘鐗嗙粊锕傛煕閺嵮勫櫧缂侇喓鍔戝鍫曟偄閸濄儱鐏遍棅
            {
                retlen = i-pos+1;
                if(retlen > DATA_PAYLOAD || retlen < 16)//闂佸搫鐗嗙粔瀛樻叏閻旂厧闂柕濞垮€楅悷鎾绘偠濞戞ɑ婀伴柡鍡欏枛楠炴垿顢氶埀顒勫汲鏉堛劍鍎熼柨鏃囨硶閻熸繈鎮洪幒鎴炲殌缂闂佺懓鐡ㄩ悧妤呭汲閻旂厧绠叉い鏃傚帶閻﹁泛顭挎０婵呯敖闁绘搩鍙冮弫宥囦沪閸撗冾棔閻庢鍠栫换瀣箔婢跺娼伴柨婵嗘礌閳
                {
                    m_receivedBlock.remove(0,i);
                    return ;
                }
                else
                {
                    data = bufptr + pos;
                    retlen = i-pos+1;

                    valid_len = frame_reverse_escape(data,retlen);
                    m_downlinkFID = (data[1] << 8) | data[2];
                    m_downlinkMSN = (bufptr[12] << 8) | bufptr[13];
                    print_data(data,valid_len);
                    OnParseValidPacket(&data[14],valid_len-14);
                    m_receivedBlock.remove(0,pos+retlen);
                    break;
                }
            }
        }
    }
}

void CTcpClient::on_timerTimeout()
{
    if(sender() != m_timer)
        return;
    if (m_client != nullptr && m_bIsConnected && getSendIntervalTime() > 100000)
    {
        //send heart-beating
        sendHeartbeat();
        //calculate minUUID
    }

    if (rand()%100 <1 && m_client == nullptr)
    {
        //1/10 chance to make new connections.
        reConnect();
    }
}
void CTcpClient::displayMessage(QString str)
{
    qDebug() << str;
}

quint32 CTcpClient::getRadomUUIDDestin()
{
    int nTotalClients = 1;
    int nMinID = ((m_maxUUID - m_minUUID) < nTotalClients) ? m_minUUID:(m_maxUUID - nTotalClients);
    int nSpan = (m_maxUUID - nMinID + 1);
    int nChoose = rand() % nSpan;

    return nMinID + nChoose ;
}

void CTcpClient::SendPacket(BD_PACKET_FUNC_ID_E fid,void *data,uint8_t res)
{
    if(!m_bIsConnected)
        return;
    uint8_t *buf = (uint8_t*)malloc(DATA_PAYLOAD);
    if(buf == NULL)
        return;
    uint16_t buflen = 0;
    switch (fid) {
    case BdTerminalStartClientTest_E:
    case BdTerminalResponse_E:
        buflen = BuildPacket(buf,fid,NULL,res);
        break;
    case BdTerminalClientTest_E:
    case BdTerminalUploadFileData_E:
    case BdTerminalDownloadFileData_E:
    case BdTerminalJson_E:
    case BdTerminalLogin_E:
    case BdTerminalRptsHeartbeat_E:
        buflen = BuildPacket(buf,fid,data,res);
        break;
    default:
        //markMsgSendSuc();
        break;
    }
    if(buflen > 0)
    {
        int no_send = buflen;
        int sent = 0;
        do{
            if(no_send >= m_nPayload)
            {
                sendData(&buf[sent], m_nPayload);
                delayMs(1);
            }
            else
                sendData(&buf[sent], no_send%m_nPayload);
            sent += m_nPayload;
            no_send -= m_nPayload;
        }while(no_send > 0);
    }
    free(buf);
}

uint16_t CTcpClient::sendData(uint8_t *ptr,uint16_t len)
{
    if(!m_bIsConnected)
        return 0;
    resetSendTime();
    print_data(ptr,len);
    QByteArray sendData((char*)ptr,len);
#if (ZP_WANTSSL!=0)
            QGHSslClient * pSockSsl = qobject_cast<QGHSslClient*>(m_client);
            QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(m_client);
#else
            QGHTcpClient * pSockTcp = qobject_cast<QGHTcpClient*>(pSock);
            if (pSockTcp)
                uuid = pSockTcp->uuid();
#endif
#if (ZP_WANTSSL!=0)
            if (pSockSsl)
                pSockSsl->SendData(sendData);
            else if (pSockTcp)
                pSockTcp->SendData(sendData);
#else
            if (pSockTcp)
                pSockTcp->SendData(sendData);
#endif
    displayMessage(QString("[%1]client %2 send len:%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(m_uuid,16,16,QChar('0')).arg(len));
    return len;
}

int CTcpClient::OnParseValidPacket(quint8 *ptr, int extdatalen)
{
    if(m_downlinkFID == BdPlarformSendFileData_E || m_uplinkFID == BdTerminalUploadFileData_E)
        updateCcp();
    switch (m_downlinkFID) {
    case BdPlatformResponse_E:
    {
        uint16_t msn = 0;
        //@msn闂佹寧绋掗宸搑responding to the uplink message serial number
        msn = (ptr[0] << 8) | ptr[1];
        //@dfId:Corresponding to the uplink setting function ID
        //2 bytes is the function ID number of the terminal reporting data
        m_downUplinkFID = (ptr[2] << 8) | ptr[3];
        //@result:Response result to the online data
        //0x00 setting successful,0x01 Setting failed
        m_ackCode = ptr[4];
        if(m_ackCode == 0x00)
            qDebug("Setting successful\n");
        else if(m_ackCode == 0x01)
            qDebug("Setting failed\n");
        else
            qDebug("Unknow Error\n");
        qDebug("Downlink Function ID:0x%04x",m_downUplinkFID);
        switch (m_downUplinkFID) {
        case BdTerminalRptsHeartbeat_E:
            qDebug("send heardbeat ok\n");
            break;
        }
        setWaitStatus(AckReceived_E);
    }
        break;
    case BdTerminalLoginResponse_E:
    {
        qDebug("Login Date Time:20%02d-%02d-%02d %02d:%02d:%02d",ptr[0],ptr[1],ptr[2],ptr[3],ptr[4],ptr[5]);
        BD_TMN_LOGIN_RESPONSE_S loginResponse;
        loginResponse.models_id = (ptr[6] << 8) | ptr[7];
        loginResponse.displacement = (ptr[8] << 8) | ptr[9];
        loginResponse.needUpgrade = ptr[10];
        loginResponse.auth = ptr[11];
        if(loginResponse.needUpgrade == 0x55)
            qDebug("need upgrade\n");
        if(loginResponse.auth >= BdUserAuthGeneral_E+1)
        {
            m_nAuthLevel = loginResponse.auth - 1;
            qDebug("Login successful\n");
        }
        else
        {
            m_nAuthLevel = -1;
            qDebug("Login failed锛%d\n", loginResponse.auth);
        }
    }
        break;
    case BdPlatformAckJson_E:
    {
        QString strJson((char*)ptr);
        QJsonParseError err;
        m_ackJson = QJsonDocument::fromJson(strJson.toUtf8(),&err);
        if (QJsonParseError::NoError != err.error)
        {
            qDebug() << err.errorString().toLatin1();
            setWaitStatus(AckParseError_E);
        }
        else
        {
            qDebug() << "m_ackJson" << m_ackJson;
            setWaitStatus(AckReceived_E);
        }
    }
        break;
    case BdPlarformSendFileData_E:
    {
        uint16_t msgpos = 0;
        m_downlodaData.currently_sent_bytes = get4bytes(&ptr[msgpos],&msgpos);
        m_downlodaData.sent_bytes = get4bytes(&ptr[msgpos],&msgpos);
        m_downlodaData.not_sent_bytes = get4bytes(&ptr[msgpos],&msgpos);
        m_downlodaData.file_size = get4bytes(&ptr[msgpos],&msgpos);
        uint32_t datalen = sizeof (m_downlodaData.file_data);
        if(m_downlodaData.currently_sent_bytes > datalen)
            setWaitStatus(AckSendDataError_E);
        else
        {
            memcpy(m_downlodaData.file_data,&ptr[msgpos],m_downlodaData.currently_sent_bytes);
            msgpos += m_downlodaData.currently_sent_bytes;
            setWaitStatus(AckReceived_E);
        }
    }
        break;
    default:
        qDebug("Other Function ID\n");
        break;
    }
    return 0;
}

void CTcpClient::login()
{
    BD_TMN_LOGIN_INFO_S loginInfo;
    memset(&loginInfo,0,sizeof(BD_TMN_LOGIN_INFO_S));
    loginInfo.terminal_type = 0x55;
    snprintf((char*)loginInfo.user_name,sizeof (loginInfo.user_name),"%s",m_userName.toLocal8Bit().data());
    snprintf((char*)loginInfo.password,sizeof (loginInfo.password),"%s",m_password.toLocal8Bit().data());
    SendPacket(BdTerminalLogin_E,&loginInfo);
}

void CTcpClient::delayMs(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void CTcpClient::resetSendTime()
{
    m_lastSendTime = QDateTime::currentMSecsSinceEpoch();
}

qint64 CTcpClient::getSendIntervalTime(void)
{
    return QDateTime::currentMSecsSinceEpoch() - m_lastSendTime;
}


bool CTcpClient::proxyCall(BD_JSON_REQUEST_CODE_E nCode, void *data, QJsonDocument &ackDoc)
{
    //婵犵鈧啿鈧綊鎮樻径搴ｇ杸闁告劦鍘鹃崕鏌ユ煕閺嵮勫櫣婵犫偓椤忓嫷娼伴柕鍫濆椤撴椽鏌涢幘宕囆㈤柛鎴磿缁辨帟绠涢幘宕囧矝闂佸憡鍨圭亸銊ф濠靛绀嗘繛鍡樻尰娴犳绱掑☉姗嗘Ц缂佸墎鍠曠粻娑㈠礃椤撶姴鍔滈梺鍛婄墪閹虫挾鎹㈤幋锕€鐐婇柣鎰絻閺呮瑩鏌涘▎鎰伌闁逞屽厸閻掞妇绮旈悜钘夌畳
    int wait_cnt = 60000;
    while ((wait_cnt--) && (!m_heartbeatAckReturned)) {
        delayMs(1);
    }
    if(m_heartbeatAckReturned == false) //缂傚倸鍟崹鍦垝閸洘鍋愰柤鍝ヮ暯閸嬫挻鎷呴崫銉э紳闁
    {
        emit evt_ShowTips("The network status is abnormal!");
        return false;
    }
    QJsonDocument sendJson;
    QJsonObject jsonObj;
    QJsonObject dataObj;
    CCommon *pCommon = CCommon::Instance();
    jsonObj["RequestCode"] = nCode;
    switch (nCode) {
    case BdRequestSaveProductInfo_E:
    {
        PRODUCT_INFO_S *pInfo = (PRODUCT_INFO_S*)data;
        if(pInfo->productName.length() <= 0 || pInfo->saveFilePath.length() <= 0)
            return false;
        dataObj["ProductName"] = pInfo->productName;
        dataObj["ProductTypeId"] = QString::number(pInfo->productTypeId);
        dataObj["Date"] = pInfo->date;
        dataObj["ProductDesp"] = pInfo->productDesp;
        QJsonObject crcObj;
        pCommon->PutVersionInfo(pInfo->crcDefaultVersion,crcObj);
        dataObj["CrcDefaultVersion"] = crcObj;
        dataObj["SaveFilePath"] = pInfo->saveFilePath;
        QJsonArray crcArray;
        foreach (VERSION_INFO_S info, pInfo->crcVersionList) {
            QJsonObject crcObj;
            pCommon->PutVersionInfo(info,crcObj);
            crcArray << crcObj;
        }
        dataObj["CrcVersionList"] = crcArray;
        {
            QMapIterator<QString,MCU_INFO_S> i(pInfo->mcuInfos);
            QJsonArray mcuTypeArray;
            while (i.hasNext()) {
                i.next();
                QJsonObject mcuTypeObj;
                mcuTypeObj["McuTypeName"] = i.value().mcuTypeName;
                mcuTypeObj["McuTypeId"] = QString::number(i.value().mcuTypeId);
                QJsonObject mcuObj;
                pCommon->PutVersionInfo(i.value().mcuDefaultVersion,mcuObj);
                mcuTypeObj["McuDefaultVersion"] = mcuObj;

                QJsonArray mcuArray;
                foreach (VERSION_INFO_S info, i.value().mcuVersionList) {
                    QJsonObject mcuObj;
                    pCommon->PutVersionInfo(info,mcuObj);
                    mcuArray << mcuObj;
                }
                mcuTypeObj["McuVersionList"] = mcuArray;
                mcuTypeArray << mcuTypeObj;
            }
            dataObj["McuInfos"] = mcuTypeArray;
        }

        {
            QJsonObject groupFileObj;
            groupFileObj["Name"] = pInfo->groupFileDefaultVersion.name;
            groupFileObj["Date"] = pInfo->groupFileDefaultVersion.date;
            groupFileObj["SavePath"] = pInfo->groupFileDefaultVersion.savePath;
            groupFileObj["Message"] = pInfo->groupFileDefaultVersion.message;
            groupFileObj["IsDefault"] = pInfo->groupFileDefaultVersion.isDefault;
            QJsonArray fileArray;
            QMapIterator<QString,VERSION_INFO_S> i(pInfo->groupFileDefaultVersion.fileInfos);
            while (i.hasNext()) {
                i.next();

                QJsonObject fileObj;
                pCommon->PutVersionInfo(i.value(),fileObj);
                fileArray << fileObj;
            }
            groupFileObj["FileInfos"] = fileArray;
            dataObj["GroupFileDefaultVersion"] = groupFileObj;
        }

        {
            QMapIterator<QString,GROUP_FILE_INFO_S> i(pInfo->groupFileInfos);
            QJsonArray groupFileInfoArray;
            while (i.hasNext()) {
                i.next();
                QJsonObject groupFileObj;
                groupFileObj["Name"] = i.value().name;
                groupFileObj["Date"] = i.value().date;
                groupFileObj["SavePath"] = i.value().savePath;
                groupFileObj["Message"] = i.value().message;
                groupFileObj["IsDefault"] = i.value().isDefault;
                QJsonArray fileArray;
                QMapIterator<QString,VERSION_INFO_S> mergeFileIter(i.value().fileInfos);
                while (mergeFileIter.hasNext()) {
                    mergeFileIter.next();
                    QJsonObject fileObj;
                    pCommon->PutVersionInfo(mergeFileIter.value(),fileObj);
                    fileArray << fileObj;
                }
                groupFileObj["FileInfos"] = fileArray;
                groupFileInfoArray << groupFileObj;
            }
            dataObj["GroupFileInfos"] = groupFileInfoArray;
        }
    }
        break;
    case BdRequestDeleteProductInfo_E:
    {
        BD_REQUEST_CRC_S *pInfo = (BD_REQUEST_CRC_S*)data;
        dataObj["ProductName"] = pInfo->productName;
    }
        break;
    case BdRequestSetDefaultCrcVersion_E:
    case BdRequestAddNewCrcVersion_E:
    case BdRequestRemoveCrcVersion_E:
    {
        BD_REQUEST_CRC_S *pInfo = (BD_REQUEST_CRC_S*)data;
        dataObj["ProductName"] = pInfo->productName;
        pCommon->PutVersionInfo(pInfo->verInfo,dataObj);
    }
        break;
    case BdRequestAddMcuType_E:
    {
        BD_REQUEST_MCU_S *pInfo = (BD_REQUEST_MCU_S*)data;
        dataObj["ProductName"] = pInfo->productName;
        dataObj["McuTypeName"] = pInfo->mcuTypeName;
    }
        break;
    case BdRequestAddNewMcuVersion_E:
    {
        BD_REQUEST_MCU_S *pInfo = (BD_REQUEST_MCU_S*)data;
        if(pInfo->productName.length() <= 0)
            return false;
        dataObj["ProductName"] = pInfo->productName;
        dataObj["McuTypeName"] = pInfo->mcuTypeName;
        pCommon->PutVersionInfo(pInfo->verInfo,dataObj);
    }
        break;
    case BdRequestSetDefaultMcuVersion_E:
    {
        BD_REQUEST_MCU_S *body = (BD_REQUEST_MCU_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["McuTypeName"] = body->mcuTypeName;
        pCommon->PutVersionInfo(body->verInfo,dataObj);
    }
        break;
    case BdRequestAddProductInfo_E:
    {
        PRODUCT_INFO_S *pInfo = (PRODUCT_INFO_S*)data;
        if(pInfo->productName.length() <= 0 || pInfo->saveFilePath.length() <= 0)
            return false;
        dataObj["ProductName"] = pInfo->productName;
        dataObj["ProductTypeId"] = QString::number(pInfo->productTypeId);
        dataObj["Date"] = pInfo->date;
        dataObj["ProductDesp"] = pInfo->productDesp;
        dataObj["SaveFilePath"] = pInfo->saveFilePath;
    }
        break;
    case BdRequestAddFileToGroupFile_E:
    {
        BD_REQUEST_GROUP_S *pInfo = (BD_REQUEST_GROUP_S*)data;
        if(pInfo->productName.length() <= 0 || pInfo->savePath.length() <= 0)
            return false;
        dataObj["ProductName"] = pInfo->productName;
        dataObj["Name"] = pInfo->name;
        dataObj["Date"] = pInfo->date;
        dataObj["SavePath"] = pInfo->savePath;
        dataObj["Message"] = pInfo->message;
        dataObj["IsDefault"] = pInfo->isDefault;
        QJsonObject fileObj;
        pCommon->PutVersionInfo(pInfo->verInfo, fileObj);
        dataObj["FileInfo"] = fileObj;
    }
        break;
    case BdRequestStopDownloadFile_E:
    case BdRequestStopUploadFile_E:
    case BdRequestQueryProductList_E:
        break;
    case BdRequestQueryProductInfo_E:
        dataObj["ProductName"]  = QString((char*)data);
        break;
    case BdRequestUploadFile_E:
    {
        MSS = 896;
        m_ccp.cwnd_gain = 2;
        BD_REQUEST_UPLOAD_FILE_S *body = (BD_REQUEST_UPLOAD_FILE_S*)data;
        dataObj["RemoteFilePath"] = body->remoteFilePath;
        dataObj["RemoteFileName"] = body->remoteFileName;
        dataObj["FileSize"] = QString::number(body->fileSize);
    }
        break;
    case BdRequestDownloadFile_E:
    {
        MSS = 1000;
        m_ccp.cwnd_gain = 1.5;
        BD_REQUEST_DOWNLOAD_FILE_S *body = (BD_REQUEST_DOWNLOAD_FILE_S*)data;
        dataObj["RemoteFileFullPath"] = body->remoteFileFullPath;
    }
        break;
    case BdRequestRemoveMcuType_E:
    {
        BD_REQUEST_MCU_S *body = (BD_REQUEST_MCU_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["McuTypeName"] = body->mcuTypeName;
    }
        break;
    case BdRequestRemoveMcuVersion_E:
    {
        BD_REQUEST_MCU_S *body = (BD_REQUEST_MCU_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["McuTypeName"] = body->mcuTypeName;
        pCommon->PutVersionInfo(body->verInfo,dataObj);
    }
        break;
    case BdRequestRemoveGroupFile_E:
    case BdRequestAddGroupFile_E:
    {
        BD_REQUEST_EDIT_GROUP_FILE_S *body = (BD_REQUEST_EDIT_GROUP_FILE_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["Name"] = body->groupFileInfo.name;
        dataObj["Date"] = body->groupFileInfo.date;
        dataObj["SavePath"] = body->groupFileInfo.savePath;
        dataObj["Message"] = body->groupFileInfo.message;
        dataObj["IsDefault"] = body->groupFileInfo.isDefault;
//        QJsonArray fileArray;
//        QMapIterator<QString,VERSION_INFO_S> groupFileIter(body->groupFileInfo.fileInfos);
//        while (groupFileIter.hasNext()) {
//            groupFileIter.next();
//            QJsonObject fileObj;
//            pCommon->PutVersionInfo(groupFileIter.value(),fileObj);
//            fileArray << fileObj;
//        }
//        groupFileObj["FileInfos"] = fileArray;
//        dataObj["GroupFileInfo"] = groupFileObj;
    }
        break;
    case BdRequestRemoveFilesFromGroupFile_E:
    {
        BD_REQUEST_GROUP_S *body = (BD_REQUEST_GROUP_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["Name"] = body->name;
        dataObj["SubFileName"] = body->verInfo.name;
    }
        break;
    case BdRequestSetDefaultGroupFileVersion_E:
    {
        BD_REQUEST_GROUP_S *body = (BD_REQUEST_GROUP_S*)data;
        dataObj["ProductName"]  = body->productName;
        dataObj["Name"] = body->name;
        dataObj["SubFileName"] = body->verInfo.name;
    }
        break;
    case BdRequestAddLog_E:
    {
        BD_REQUEST_LOG_S *body = (BD_REQUEST_LOG_S*)data;
        dataObj["ProductName"] = body->productName;
        dataObj["DevNumber"] = body->devNumber;
        dataObj["ImeiNumber"] = body->imeiNumber;
        dataObj["FwVersion"] = body->fwVersion;
        dataObj["Type"] = body->type;
        dataObj["Subtype"] = body->subtype;
        dataObj["Result"] = body->result;
        dataObj["DateTime"] = body->dateTime.toString("yyyy-MM-dd hh:mm:ss");
        dataObj["Message"] = body->message;
    }
        break;
    case BdRequestQueryLog_E:
    {
        BD_REQUEST_LOG_S *body = (BD_REQUEST_LOG_S*)data;
        dataObj["ProductName"] = body->productName;
        dataObj["DevNumber"] = body->devNumber;
        dataObj["ImeiNumber"] = body->imeiNumber;
        dataObj["FwVersion"] = body->fwVersion;
        dataObj["Type"] = body->type;
        dataObj["Subtype"] = body->subtype;
        dataObj["Result"] = body->result;
        dataObj["StartDateTime"] = body->startDateTime.toString("yyyy-MM-dd hh:mm:ss");
        dataObj["EndDateTime"] = body->endDateTime.toString("yyyy-MM-dd hh:mm:ss");
        dataObj["FuzzySearch"] = body->fuzzySearch;
        dataObj["PageNo"] = body->pageNo;
        dataObj["PageSize"] = body->pageSize;
    }
        break;
    case BdRequestEditUser_E:
    case BdRequestRemoveUser_E:
    case BdRequestAddUser_E:
    {
        USER_INFO_S *body = (USER_INFO_S*)data;
        dataObj["Name"]  = body->name;
        dataObj["Password"] = body->password;
        dataObj["Auth"] = body->auth;
        dataObj["Date"] = body->date;
        dataObj["Message"] = body->message;
        QJsonArray productArray;
        foreach (QString str, body->products) {
            productArray << str;
        }
        dataObj["Products"] = productArray;
    }
        break;
    case BdRequestQueryPcClientEvents_E:
    case BdRequestGetUserList_E:
        break;
    case BdRequestDeleteFile_E:
    {
        BD_REQUEST_DELETE_FILE_S *body = (BD_REQUEST_DELETE_FILE_S*)data;
        dataObj["FileFullPath"]  = body->fileFullPath;
    }
        break;
    case BdRequestRemoveEvent_E:
    case BdRequestAddEvent_E:
    {
        EVENT_INFO_S *body = (EVENT_INFO_S*)data;
        dataObj["EventSn"] = QString::number(body->eventSn);
        dataObj["EventType"] = body->eventType;
        dataObj["IdType"] = body->idType;
        dataObj["Id"] = body->id;
        dataObj["EventPara1"] = body->eventPara1;
        dataObj["EventPara2"] = body->eventPara2;
        dataObj["AckPara1"] = body->ackPara1;
        dataObj["AckPara2"] = body->ackPara2;
        dataObj["Status"] = body->status;
    }
        break;
    case BdRequestSetEventStatus_E:
    {
        BD_REQUEST_SET_EVENT_STATUS_S *body = (BD_REQUEST_SET_EVENT_STATUS_S*)data;
        dataObj["EventSn"] = QString::number(body->eventSn);
        dataObj["Status"] = body->status;
        dataObj["AckPara1"] = body->ackPara1;
        dataObj["AckPara2"] = body->ackPara2;
    }
        break;
    default:
        return false;
    }
    jsonObj["data"] = dataObj;
    sendJson.setObject(jsonObj);
    qDebug() << "sendJson" << sendJson;
    bool res = false;
    SendPacket(BdTerminalJson_E,sendJson.toJson(QJsonDocument::Indented).data());
    if(waittingAck(60000) == AckReceived_E)
    {
        ackDoc = m_ackJson;
        QJsonObject ackJsonObj;
        ackJsonObj = m_ackJson.object();
        if(ackJsonObj.contains("code"))
        {
            if(ackJsonObj["code"].toInt() == BdExecutionSucceeded_E)
                res = true;
            emit evt_ShowTips(QString("code:%1,%2").arg(ackJsonObj["code"].toInt()).arg(ackJsonObj["msg"].toString()));
        }
    }
    return res;
}

bool CTcpClient::uploadFileData(BD_TRANSFER_FILE_DATA_S &body)
{
    bool res = false;
    SendPacket(BdTerminalUploadFileData_E,&body);
    if(waittingAck(60000) == AckReceived_E && m_ackCode == BdExecutionSucceeded_E)
        res = true;
    if(!res)
        qDebug() << "uploadFileData Failed" << waitStatus() << m_ackCode;
    return res;
}

bool CTcpClient::downloadFileData(BD_TMN_DOWNLOAD_FILE_DATA_S &body,BD_TRANSFER_FILE_DATA &tBody)
{
    bool res = false;
    SendPacket(BdTerminalDownloadFileData_E,&body);
    if(waittingAck(60000) == AckReceived_E)
    {
        tBody = m_downlodaData;
        res = true;
    }
    return res;
}

bool CTcpClient::startTest()
{
    bool res = false;
    SendPacket(BdTerminalStartClientTest_E,nullptr);

    if(waittingAck() == AckReceived_E)
    {
        m_totalSendTestByte = 0;
        m_bIsStartTest = true;
        res = true;
        displayMessage(QString("client %1 startTest ok").arg(m_uuid,16,16,QChar('0')));
    }
    return res;
}

void CTcpClient::stopTest()
{
    m_bIsStartTest = false;
}

bool CTcpClient::sendTestPacket(uint16_t nLen)
{
    displayMessage(QString("client %1 sendTestPacket:%2").arg(m_uuid,16,16,QChar('0')).arg(nLen));
    bool res = false;
    BD_TMN_CLIENT_TEST_S body;
    if(nLen > sizeof (body.test_data))
        return res;
    m_totalSendTestByte += nLen;
    for(int i=0; i<nLen; i++)
    {
        body.test_data[i] = rand();
    }
    body.currently_sent_bytes = nLen;
    body.total_sent_bytes = m_totalSendTestByte;
    SendPacket(BdTerminalClientTest_E,&body);
    if(waittingAck() == AckReceived_E && m_ackCode == BdExecutionSucceeded_E)
        res = true;
    else
        displayMessage(QString("client %1 sendTestPacket: send failed %2").arg(m_uuid,16,16,QChar('0')).arg(m_ackCode));

    return res;
}

CTcpClient::WAIT_ACK_STATUS_E CTcpClient::waittingAck(int ms)
{
    setWaitStatus(AckWaitting_E);
    int waitCnt = ms;
    while (waitCnt--) { //闂佸搫鐗冮崑鎾愁熆閼稿灚鐨戦柣鈩冨灥椤晄
        delayMs(1);
        if(waitStatus() >= AckReceived_E)
            break;
    }
    return waitStatus();
}

void CTcpClient::reConnect()
{
#if (ZP_WANTSSL!=0)
    if (m_bSsl==true)
    {
        QGHSslClient * client = new QGHSslClient(this,m_nPayload);
        m_client = client;
        connect(client, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
        //connect(client, SIGNAL(connected()),this, SLOT(on_client_connected()));
        connect(client, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
        connect(client, SIGNAL(encrypted()), this, SLOT(on_client_connected()));
        QString strCerPath =  QCoreApplication::applicationDirPath() + "/ca_cert.pem";
        QList<QSslCertificate> lstCas = QSslCertificate::fromPath(strCerPath);
        client->setCaCertificates(lstCas);
        client->connectToHostEncrypted(m_serverIp,m_serverPort);
    }
    else
    {
        QGHTcpClient * client = new QGHTcpClient(this,m_nPayload);
        m_client = client;
        connect(client, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
        connect(client, SIGNAL(connected()),this, SLOT(on_client_connected()));
        connect(client, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
        connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
        client->connectToHost(m_serverIp,m_serverPort);
        displayMessage(QString("client->connectToHost %1:%2===%3").arg(m_serverIp).arg(m_serverPort).arg(m_uuid,16,16,QChar('0')));
    }
#else
    QGHTcpClient * client = new QGHTcpClient(this,ui.horizontalSlider->value());
    m_client = client;
    connect(client, SIGNAL(readyRead()),this, SLOT(new_data_recieved()));
    connect(client, SIGNAL(connected()),this, SLOT(on_client_connected()));
    connect(client, SIGNAL(disconnected()),this,SLOT(on_client_disconnected()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(on_client_trasferred(qint64)));
    client->connectToHost(m_serverIp,m_serverPort);
#endif
}

void CTcpClient::setWaitStatus(WAIT_ACK_STATUS_E nStatus)
{
    m_waitMutex.lock();
    m_bWaittingAckStatus = nStatus;
    m_waitMutex.unlock();
}

CTcpClient::WAIT_ACK_STATUS_E CTcpClient::waitStatus()
{
    m_waitMutex.lock();
    WAIT_ACK_STATUS_E status = m_bWaittingAckStatus;
    m_waitMutex.unlock();
    return status;
}

void CTcpClient::updateSentBytes(quint64 nBytes)
{
    CMyAutoMutex autoMutex(&S_mBytesRateMutex);
    S_nSentBytes += nBytes;
}

quint64 CTcpClient::getSentBytes()
{
    CMyAutoMutex autoMutex(&S_mBytesRateMutex);
    return S_nSentBytes;
}

void CTcpClient::updateRecBytes(quint64 nBytes)
{
    CMyAutoMutex autoMutex(&S_mBytesRateMutex);
    S_nRecBytes += nBytes;
}

quint64 CTcpClient::getRecBytes()
{
    CMyAutoMutex autoMutex(&S_mBytesRateMutex);
    return S_nRecBytes;
}

void CTcpClient::updateCcp()
{
    m_ccp.last_rtt_ms = m_ccp.curr_rtt_ms;
    m_ccp.curr_rtt_ms = QDateTime::currentMSecsSinceEpoch() - m_lastSendTime;
    //qDebug() << "m_ccp.curr_rtt_ms" << m_ccp.curr_rtt_ms << m_ccp.curr_cwnd_bytes << m_ccp.min_rtt_ms;

    if(m_ccp.min_rtt_ms > m_ccp.curr_rtt_ms)
        m_ccp.min_rtt_ms = m_ccp.curr_rtt_ms;
    bool isSlowStart=true;
    //婵炵鍋愭慨鍓ф椤撱垹鏋侀柣妤€鐗嗙粊
    if(m_ccp.curr_cwnd_bytes<ssthresh){//闂侀€涚┒閸ㄥ綊骞嗘惔銊ョ
    }else{//cwnd>ssthresh  闂佽鐏氶崕閬嶃€侀敐澶嬬劶闁割煈鍠栫敮
        isSlowStart=false;
    }

    //闂佸搫鐗滈崜婵嬫偪閸℃稑鏋侀柣妤€鐗嗙粊锕€霉閼测晛鞋缂侀鍘鹃埀顒傛嚀閺堫剟鎯侀鐐存櫖閻忕偟鏅壕璇测攽椤旂⒈鍎忛柛銊ょ矙瀵剟顢橀悢鎰燂箓鏌涘楣冩閻庢哎鍨虹换
    int crow = NORMAL;
    int rtt_thresh_ms = m_ccp.min_rtt_ms*5;
    if(m_ccp.curr_rtt_ms > rtt_thresh_ms){//p%闂佹眹鍔岀€氼參銆呰閹娊宕惰缁叉椽鏌ｉ姀銏犳瀾閻庢哎鍨虹换
        if(m_ccp.curr_rtt_ms > rtt_thresh_ms){//50%濠殿喗甯掗崐璇差啅閼测晜鎯ラ柛娑卞枟椤
            crow = TIME_OUT;
        }else{//50%濠殿喗甯掗崐璇差啅閸忓吋浜ら柡鍌涘缁€鈧婵炴垶鎼╂禍顏堝闯閸涘﹤绶炵€光偓閻＄瓈 婵炴垶姊婚崰搴＄暤閸℃稑鍙婃い鏍ㄧ瑜般儵姊洪銈呮灈闁革絽鎲＄€
            crow = THREE_DUP_ACK;
        }
    }
    if(!crow){//濠电偛澶囬崜婵嗭耿娓氣偓楠炲繘濡烽妷顔芥殎
        if(isSlowStart){//闂侀€涚┒閸ㄥ綊骞嗘惔銊ョ
            m_ccp.curr_cwnd_bytes*=m_ccp.cwnd_gain;//缂備焦鍔栭〃鍛般亹濞戙垹绀夐柣妯荤ゴ閸
        }else{//闂佽鐏氶崕閬嶃€侀敐澶嬬劶闁割煈鍠栫敮
            m_ccp.curr_cwnd_bytes+=MSS*(1.0*MSS/m_ccp.curr_cwnd_bytes)*m_ccp.curr_cwnd_bytes/MSS;
        }
    }else {

        if(m_ccp.curr_rtt_ms > rtt_thresh_ms)
            delayMs(m_ccp.min_rtt_ms);

        if(MSS == 512)
        {
            if(m_ccp.curr_rtt_ms > rtt_thresh_ms*2)
                m_ccp.curr_cwnd_bytes = 2000;
            else if(m_ccp.curr_rtt_ms > rtt_thresh_ms*3)
                m_ccp.curr_cwnd_bytes = 1000;
            else if(m_ccp.curr_rtt_ms > rtt_thresh_ms*4)
                m_ccp.curr_cwnd_bytes = 500;
            else
                m_ccp.curr_cwnd_bytes = 8000;
        }
    }

    if(m_ccp.curr_cwnd_bytes > 16384)
        m_ccp.curr_cwnd_bytes = 16384;
    if(m_ccp.curr_cwnd_bytes < MSS)
        m_ccp.curr_cwnd_bytes = MSS;

}

void CTcpClient::resetCcp()
{
    m_ccp.min_rtt_ms = 200000;
    m_ccp.curr_rtt_ms = 0;
    m_ccp.curr_cwnd_bytes = 1*MSS;
    ssthresh = 3*MSS;
}

void CTcpClient::sendHeartbeat()
{
    m_heartbeatAckReturned = false;
    SendHeartbeatPacket();
    waittingAck(60000);
    if(waitStatus() != AckReceived_E)
    {
        emit evt_ShowTips("An error occurred in the network connection!");
    }
    else
        m_heartbeatAckReturned = true;
}


