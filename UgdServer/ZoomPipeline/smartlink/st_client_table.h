#ifndef ST_CLIENT_TABLE_H
#define ST_CLIENT_TABLE_H

#include <QObject>
#include <QList>
#include <QMutex>
#include <unordered_map>
#include <unordered_map>
#include "../network/zp_net_threadpool.h"
#include "../pipeline/zp_pipeline.h"
#include "./st_message.h"
#include "../database/databaseresource.h"
#include "../cluster/zp_clusterterm.h"
//#include "./st_cross_svr_node.h"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "ccodec.h"
#include "dispatcher.h"
class QTimer;

using namespace BdUgdServer;
#ifdef USE_PROTOBUF
class CClientNode;
#endif
namespace ExampleServer{
#ifndef USE_PROTOBUF
    class st_clientNode_baseTrans;
#endif
#ifdef USE_PROTOBUF
    typedef  boost::weak_ptr<CClientNode> NodeWkPtr;
    typedef  boost::shared_ptr<CClientNode> NodePtr;
    typedef std::unordered_map<quint64, NodeWkPtr> WkUuidNodeContainer;
    typedef std::unordered_map<quint64, NodePtr> UuidNodeContainer;
    typedef std::unordered_map<QObject *, NodePtr> SockNodeContainer;
#else
    typedef  boost::weak_ptr<st_clientNode_baseTrans> NodeWkPtr;
    typedef  boost::shared_ptr<st_clientNode_baseTrans> NodePtr;
    typedef std::unordered_map<quint64, NodeWkPtr> WkUuidNodeContainer;
    typedef std::unordered_map<quint64, st_clientNode_baseTrans> UuidNodeContainer;
    typedef std::unordered_map<QObject *, st_clientNode_baseTrans> SockNodeContainer;
#endif
	class st_client_table : public QObject
	{
		Q_OBJECT
	public:
		explicit st_client_table(
				ZPNetwork::zp_net_Engine * NetEngine
				,ZPTaskEngine::zp_pipeline * taskeng
				,ZPDatabase::DatabaseResource *pDb
				,ZP_Cluster::zp_ClusterTerm * pCluster
                ,QObject *parent = nullptr);
		~st_client_table();


        size_t ActiveNodes();
		int heartBeatingThrd();
        void setHeartBeatingThrd(int h) ;

		//Database and disk resources
		QString Database_UserAcct();
		void setDatabase_UserAcct(QString  s);
		QString Database_Event();
		void setDatabase_Event(QString  s);
		QString largeFileFolder();
		void setLargeFileFolder(QString  s);

		ZPDatabase::DatabaseResource * dbRes();

		//reg new uuids in m_hash_remoteClient2SvrName
        void cross_svr_add_uuids(QString  svrname,quint64 * pUUIDs, int nUUIDs);
		//del uuids in m_hash_remoteClient2SvrName, pUUIDs =0 means del all uuids belong to svrname
        void cross_svr_del_uuids(QString  svrname, quint64 *pUUIDs , int nUUIDs);
		//Tell remote servers of uuid-change
        void broadcast_client_uuid(quint64 uuid, bool bActive);
		//Trans user Data
		void cross_svr_send_data(QString  svrname,QByteArray  arr);
		//Server Name find
        QString cross_svr_find_uuid(quint64 uuid);

		//Cluster Global Balance
		bool NeedRedirect(quint8 bufAddresses[/*64*/],quint16 * pnPort);

		void setBalanceMax(int nmax);
        int balanceMax();


	protected:
        static const int S_REMOVE_DEAD_NODE_TIMEOUT = 20;
        static const int S_ACTIVE_TIMEOUT = 90;    //如果任务节点超过一定时间未活跃，则可以删除该节点

		//Very important hashes. will be improved for cross-server transfer
        //QMutex m_hash_mutex;
#ifdef USE_PROTOBUF
        boost::scoped_ptr<CClientNode> m_codec;
#endif
        WkUuidNodeContainer m_hash_uuid2node;
        SockNodeContainer m_hash_sock2node;

        volatile size_t m_client_nodes_size;

		//Concurrent Network frame work
        ZPNetwork::zp_net_Engine * m_pThreadEngine;
		//The piple-line
		ZPTaskEngine::zp_pipeline * m_pTaskEngine;
		//The database pool
		ZPDatabase::DatabaseResource * m_pDatabaseRes;
		//The Server Cluster Group
        //ZP_Cluster::zp_ClusterTerm * m_pCluster;


		//The max seconds before dead client be kicked out
		int m_nHeartBeatingDeadThrd;
		//Database Resource Names used by nodes
		QString m_strDBName_useraccount;
		QString m_strDBName_event;
		QString m_largeFileFolder;

		//Cluster max balance value, when clients exceeds this val, balance will happen.
		int m_nBalanceMax;

		//cluster Nodes Map
        std::unordered_map<quint64,QString> m_hash_remoteClient2SvrName;
		QMutex m_mutex_cross_svr_map;
		//Cluster Node Factory
		ZP_Cluster::zp_ClusterNode * cross_svr_node_factory(
				ZP_Cluster::zp_ClusterTerm * /*pTerm*/,
				QObject * /*psock*/,
                QObject * /*parent*/);

    signals:
        void evt_addNewClient(QObject *pSock);
        void evt_clientClose(QObject *pSock);
        void evt_AddNewClientOk(QObject *pSock);

    public slots:
		//this event indicates new client connected.
        void on_evt_NewClientConnected(QObject * /*clientHandle*/, QByteArray datablock);
		//this event indicates new client encrypted.
		void on_evt_ClientEncrypted(QObject * /*clientHandle*/);
		//this event indicates a client disconnected.
		void on_evt_ClientDisconnected(QObject * /*clientHandle*/);
		//some data arrival
		void on_evt_Data_recieved(QObject *  /*clientHandle*/,QByteArray  /*datablock*/ );
		//a block of data has been successfuly sent
		void on_evt_Data_transferred(QObject *   /*clientHandle*/,qint64 /*bytes sent*/);

		//this event indicates new svr successfully hand-shaked.
		void on_evt_NewSvrConnected(QString /*svrHandle*/);
		//this event indicates a client disconnected.
		void on_evt_NewSvrDisconnected(QString /*svrHandle*/);
		//some data arrival
		void on_evt_RemoteData_recieved(QString /*svrHandle*/,QByteArray  /*array*/ );
		//a block of data has been successfuly sent
        void on_evt_RemoteData_transferred(QObject *  /*svrHandle*/,qint64 /*bytes sent*/);
	public slots:
		//send msg to uuid
        bool SendToNode(quint64 uuid, QByteArray  msg);
        void KickDeadClients();

    private:
        //下面函数未加互斥锁，外部不能直接调用
#ifdef USE_PROTOBUF
        bool regisitClientUUID(CClientNode *);
        NodeWkPtr clientNodeFromUUID(quint64);
        NodeWkPtr clientNodeFromSocket(QObject *);
#else
        bool regisitClientUUID(st_clientNode_baseTrans *);
        boost::weak_ptr<st_clientNode_baseTrans> clientNodeFromUUID(quint64);
        boost::weak_ptr<st_clientNode_baseTrans> clientNodeFromSocket(QObject *);
#endif
	};
}
#endif // ST_CLIENT_TABLE_H
