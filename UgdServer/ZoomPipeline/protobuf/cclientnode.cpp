#include "cclientnode.h"
#include <QDateTime>
#include "st_message.h"
#include "st_global_def.h"
#include "st_client_file.h"
#include "casiodatabase.h"

CClientNode::CClientNode(const TcpSocketPtr &pSock, bool bIsCodec, QObject *parent)
    : zp_plTaskBase(parent)
    , sock_(pSock)
    , isCodec_(bIsCodec)
    , dispatcher_(boost::bind(&CClientNode::onUnknownMessage, this, _1, _2))
    , codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_, _1, _2))
{
    bUUIDRecieved_ = false;
    uuid_ = 0xffffffffffffffff;//Not Valid
    bTermSet = false;
    lastReportSec_ = QDateTime::currentSecsSinceEpoch();

    dispatcher_.registerMessageCallback<Heartbeat>(boost::bind(&CClientNode::onHeartBeat, this, _1, _2));
    dispatcher_.registerMessageCallback<Query>(boost::bind(&CClientNode::onQuery, this, _1, _2));

    if(bIsCodec)
    {
        CBuffer buffer;
        fneger::Heartbeat heartbeat;
        heartbeat.set_id(888888);
        heartbeat.set_timestamp(0);
        codec_.send(pSock, heartbeat);
        //ProtobufCodec::fillEmptyBuffer(&buffer, heartbeat);

        codec_.onMessage(pSock, &buffer);
    }

    fileTool_.reset(new BdUgdServer::st_client_file());
}

void CClientNode::resetNode()
{
    bUUIDRecieved_ = false;
    uuid_ = 0xffffffffffffffff;//Not Valid
    bTermSet = false;
    QMutexLocker lock(&rawDatasMutex_);
    rawDatas_.clear();
    buffer_.clear();
}

QObject * CClientNode::sock()
{
    return sock_.get();
}

//judge whether id is valid.
bool CClientNode::bIsValidUserId(qint64 id)
{
    return id >=0x01 && id <=0xFFFFFFFFFFFFFFFE;
}

void CClientNode::setClientSock(const TcpSocketPtr &pSock)
{
    sock_ = pSock;
}

//push new binary data into queue
int CClientNode::pushNewData(const  QByteArray &  dtarray)
{
    //qDebug() << "Received Data Len" << dtarray.size();
    int res = 0;
    {
        QMutexLocker lock(&rawDatasMutex_);
        res = rawDatas_.size() > 0 ? 2 : 1;
        rawDatas_.push_back(dtarray);
    }
    lastReportSec_ = QDateTime::currentSecsSinceEpoch();
    return res;
}

//The main functional method, will run in thread pool
int CClientNode::run()
{
    if (bTermSet==true)
    {
        //qDebug()<<QString("%1(%2) Node Martked Deleted, return.\n").arg((unsigned int)this).arg(ref());
        return 0;
    }

    int blocks;
    {
        QMutexLocker lock(&rawDatasMutex_);
        blocks = rawDatas_.size();
    }

    if(blocks > 0)
    {
        buffer_.clear();
        {
            quint32 msgLen, totalLen = 0;
            {
                QMutexLocker lock(&rawDatasMutex_);
                QByteArray &ba = rawDatas_.front();
                msgLen = CBuffer::peekInt32(ba.data(), ba.size());
                foreach (const QByteArray &ba, rawDatas_) {
                   totalLen += ba.size();
                }
            }
            if(msgLen == 0 || totalLen < msgLen) //消息未接收完成
                return -1;
			else if (msgLen > CBuffer::S_BUFFER_MAX_SIZE ) //非法数据包
			{
				QMutexLocker lock(&rawDatasMutex_);
				rawDatas_.clear();
				return -1;
			}
            totalLen = 0;
            {
                QMutexLocker lock(&rawDatasMutex_);
                foreach (const QByteArray &ba, rawDatas_) {
                    totalLen += ba.size();
                    if(totalLen > msgLen) //存在粘包
                    {
                        int validLen = ba.size() - (totalLen - msgLen);
                        buffer_.append(ba.data(), validLen);
                        QByteArray remainingDt(ba.data() + validLen, totalLen - msgLen);
                        rawDatas_.pop_front();
                        rawDatas_.push_front(remainingDt);
                        break;
                    }
                    else
                    {
                        buffer_.append(ba.data(), ba.size());
                        rawDatas_.pop_front();
                    }
                }
            }
        }
        codec_.onMessage(sock_, &buffer_);
    }
    return 0;
}

uint16_t CClientNode::sendData(uint8_t *ptr,uint16_t len)
{
    QByteArray sendData((char*)ptr,len);
    Q_EMIT evt_SendDataToClient(sock_.get(),sendData);
    return len;
}

bool CClientNode::checkHeartBeating(int nThreshold)
{
    qint64 currSec = QDateTime::currentSecsSinceEpoch();
    if (currSec - lastReportSec_ >= nThreshold)
    {
        qWarning() << tr("Client ") + QString("%1").arg((unsigned int)((quint64)this)) + tr(" is dead, kick out.");
        Q_EMIT evt_CloseClient(sock_.get());
    }
    return false;
}

bool CClientNode::filterMessage(qint64 nUUid)
{
    if(bUUIDRecieved_ == false)
    {
        if (bIsValidUserId( nUUid) )
        {
            bUUIDRecieved_ = true;
            uuid_ =  nUUid;
            //regisit client node to hash-table;
            //m_pClientTable->regisitClientUUID(this);
        }
        else //Invalid
        {
            qWarning() << "Client ID is invalid! Close client immediatly." << QString("id = %1").arg(nUUid,16,16,QChar('0'));
            Q_EMIT evt_CloseClient(sock_.get());
            return false;
        }
    }
    else
    {
        if (!( bIsValidUserId(nUUid)|| (nUUid==0xffffffffffffffff)))
        {
            qWarning() << "Client ID is invalid! Close client immediatly.";
            Q_EMIT evt_CloseClient(sock_.get());
            return false;
        }
        if (bIsValidUserId(nUUid)==true && uuid_ != nUUid)
        {
            qWarning() << tr("Client ID Changed in Runtime! Close client immediatly.") +
                          QString("new id = %1,old id = %2.%3").arg(nUUid,16,16,QChar('0')).arg(uuid_,16,16,QChar('0')).arg((quint64)this);
            Q_EMIT evt_CloseClient(sock_.get());
            return false;
        }
    }
    if(isCodec_)
        return false;
    else
        return true;
}

void CClientNode::onUnknownMessage(const TcpSocketPtr& conn,const MessagePtr& message)
{
    qDebug() << "onUnknownMessage: " << message->GetTypeName().c_str();
    conn->disconnectFromHost();
}

void CClientNode::onHeartBeat(const TcpSocketPtr& conn, const HeartbeatPtr& heartbeat)
{
    qDebug() << __FUNCTION__ << __LINE__;
    if(filterMessage(heartbeat->id()))
    {
        Heartbeat heartbeat;
        heartbeat.set_id(uuid_);
        heartbeat.set_timestamp(QDateTime::currentSecsSinceEpoch());
        codec_.send(conn, heartbeat);
    }
}

void CClientNode::onQuery(const TcpSocketPtr& conn, const QueryPtr &query)
{
    qDebug() << __FUNCTION__ << __LINE__;
    if(filterMessage(query->id()))
    {
        Answer answer;
        answer.set_id(uuid_);
        answer.set_query_code(query->query_code());
        switch (query->query_code()) {
        case QueryDefaultVersion:
            do
            {
                QJsonObject ackJsonObj;
                QJsonParseError err;
                QJsonDocument queryDoc = QJsonDocument::fromJson(QString(query->json_body().c_str()).toUtf8(),&err);
                if (QJsonParseError::NoError != err.error)
                {
                    qWarning() << err.errorString().toLatin1();
                    answer.set_result_code(QueryFailed);
                    break;
                }
                else
                {
                    //qDebug() << "m_ackJson" << queryDoc;
                }
                QJsonObject dataObj = queryDoc.object();
                if(!dataObj.contains("ProductName") || !dataObj.contains("FileType") || !dataObj.contains("FileSubType"))
                {
                    answer.set_result_code(QueryFailed);
                    answer.set_tips("Json parse error!");
                    break;
                }
                QUERY_DEFAULT_VERSION_S queryBody;
                queryBody.productName = dataObj["ProductName"].toString();
                queryBody.fileType = dataObj["FileType"].toString();
                queryBody.fileSubType = dataObj["FileSubType"].toString();
                if(dataObj.contains("Custom"))
                    queryBody.custom = dataObj["Custom"].toString();
                QUERY_DB_PARAMS_S params;
                params.queryCode = query->query_code();
                params.queryBody = queryBody;

                params.callback = boost::bind(&CClientNode::onDbQueryCallback, this, _1);
                CAsioDatabase::Instance()->addDbQuery(boost::bind(&CAsioDatabase::joinQueryItems, _1),
                                                      params);
                return;
            }while(0);
            break;
        }
        answer.set_timestamp(QDateTime::currentSecsSinceEpoch());
        codec_.send(conn, answer);
    }
}

void CClientNode::onDbQueryCallback(QUERY_DB_PARAMS_S &params)
{
    Answer answer;
    answer.set_id(uuid_);
    answer.set_query_code(params.queryCode);
    switch (params.queryCode) {
    case QueryDefaultVersion:
        do
        {
            if(!params.result)
            {
                answer.set_result_code(QueryFailed);
                answer.set_tips("Query default version failed!");
                break;
            }

            QJsonObject ackJsonObj;

            QList<BODY_CRC_VERSION_INFO_S> infos2 =  boost::any_cast<QList<BODY_CRC_VERSION_INFO_S>>(params.dbBodys);
            BODY_PRODUCT_INFO_S &info1 = infos2.first().productInfo;
            QUERY_DEFAULT_VERSION_S info2 = boost::any_cast<QUERY_DEFAULT_VERSION_S>(params.queryBody);

            if(info1.savePath.isEmpty() || info1.savePath == "")
            {
                answer.set_result_code(QueryFailed);
                answer.set_tips("Product information parsing error!");
                break;
            }

            bool finded = false;
            GS_DB_BODY_C body;
            foreach (BODY_CRC_VERSION_INFO_S info, infos2) {
                if(info.custom == info2.custom) //找到指定版本
                {
                    QJsonObject crcObj;
                    body = info;
                    fileTool_->putInfo2Json(TB_CRC_VERSION_INFO_E, body, crcObj);
                    ackJsonObj["SaveFilePath"] = info1.savePath;
                    ackJsonObj["VersionInfo"] = crcObj;
                    ackJsonObj["Custom"] = info2.custom;
                    finded = true;
                    break;
                }
            }

            if(finded)
            {
                QJsonDocument resultDoc;
                resultDoc.setObject(ackJsonObj);
                answer.set_json_body(resultDoc.toJson(QJsonDocument::Indented).data());
                answer.set_result_code(QuerySucc);
                answer.set_tips("Query version successfully!");
            }
            else
            {
                answer.set_result_code(QueryFailed);
                answer.set_tips("The default version do not exists!");
            }
        }while(0);
        break;
    }
    qDebug() << answer.tips().c_str();
    answer.set_timestamp(QDateTime::currentSecsSinceEpoch());
    codec_.send(sock_, answer);
}
