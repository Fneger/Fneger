#ifndef CCLIENTNODE_H
#define CCLIENTNODE_H

#include "../pipeline/zp_pltaskbase.h"
#include "boost/weak_ptr.hpp"
#include "casiotcpsocket.h"
#include "ccodec.h"
#include "dispatcher.h"
#include "protobuf_message.pb.h"
#include "cbuffer.h"
#include "casiodatabase.h"

using namespace GsGlobalDef;
using namespace fneger;

typedef boost::shared_ptr<Heartbeat> HeartbeatPtr;
typedef boost::shared_ptr<Query> QueryPtr;
typedef boost::shared_ptr<Answer> AnswerPtr;

namespace BdUgdServer {
class st_client_file;
}

using namespace ZPTaskEngine;
class CClientNode : public zp_plTaskBase
{
    Q_OBJECT
public:
    explicit CClientNode(const TcpSocketPtr &pSock, bool bIsCodec = false, QObject *parent = nullptr);
    virtual void resetNode();
    void setClientSock(const TcpSocketPtr &pSock);
    qint64 uuid() const { return uuid_; }
    bool uuidValid() const { return bUUIDRecieved_; }
    //push new binary data into queue
    int pushNewData(const  QByteArray &  dtarray);
    bool checkHeartBeating(int nThreshold);
    QObject * sock();
    bool bTermSet;
    int run();

protected:
    uint16_t sendData(uint8_t *ptr,uint16_t len);
    bool filterMessage(qint64 nUUid);
    void onUnknownMessage(const TcpSocketPtr& conn, const MessagePtr& message);
    void onHeartBeat(const TcpSocketPtr& conn, const HeartbeatPtr& heartbeat);
    void onQuery(const TcpSocketPtr& conn, const QueryPtr &query);
    void onDbQueryCallback(QUERY_DB_PARAMS_S &params);
    bool bIsValidUserId(qint64 id);


Q_SIGNALS:
    void evt_CloseClient(QObject * pSock);
    void evt_SendDataToClient(QObject * pSock,QByteArray   dtarray);

public slots:

private:
    bool bUUIDRecieved_;
    qint64 uuid_;  //Client ID
    //The raw data queue and its mutex
    QList<QByteArray> rawDatas_;
    QMutex rawDatasMutex_;
    qint64 lastReportSec_;
    TcpSocketPtr sock_;
    bool isCodec_;   //作为codec使用
    ProtobufDispatcher dispatcher_;
    ProtobufCodec codec_;
    CBuffer buffer_;
    boost::scoped_ptr<BdUgdServer::st_client_file> fileTool_;

};

#endif // CCLIENTNODE_H
