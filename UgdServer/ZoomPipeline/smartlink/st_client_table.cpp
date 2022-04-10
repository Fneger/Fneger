#include "st_client_table.h"
#ifdef USE_PROTOBUF
#include "cclientnode.h"
#else
#include "st_clientnode_applayer.h"
#endif

#include <assert.h>
//#include "st_cross_svr_node.h"
//#include "st_cross_svr_msg.h"
#include <functional>
#include <QList>
#include <QStringList>
#include <QTcpSocket>
#include "st_client_event.h"
#include <QTimer>
#include "cgarbagecollector.h"

namespace ExampleServer{
	using namespace std::placeholders;
	st_client_table::st_client_table(
			ZPNetwork::zp_net_Engine * NetEngine,
			ZPTaskEngine::zp_pipeline * taskeng,
			ZPDatabase::DatabaseResource * pDb,
			ZP_Cluster::zp_ClusterTerm * pCluster,
			QObject *parent) :
		QObject(parent)
	  ,m_pThreadEngine(NetEngine)
	  ,m_pTaskEngine(taskeng)
	  ,m_pDatabaseRes(pDb)
      //,m_pCluster(pCluster)
      ,m_nBalanceMax(10240)
	{

		m_nHeartBeatingDeadThrd = 180;
		connect (m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_NewClientConnected,this,&st_client_table::on_evt_NewClientConnected,Qt::QueuedConnection);
		connect (m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_ClientEncrypted,this,&st_client_table::on_evt_ClientEncrypted,Qt::QueuedConnection);
		connect (m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_ClientDisconnected,this,&st_client_table::on_evt_ClientDisconnected,Qt::QueuedConnection);
        connect (m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_Data_recieved,this,&st_client_table::on_evt_Data_recieved,Qt::QueuedConnection);
		connect (m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_Data_transferred,this,&st_client_table::on_evt_Data_transferred,Qt::QueuedConnection);
        connect (this, &st_client_table::evt_AddNewClientOk, m_pThreadEngine, &ZPNetwork::zp_net_Engine::evt_AddNewClientOk, Qt::QueuedConnection);
#if 0
		connect (m_pCluster,&ZP_Cluster::zp_ClusterTerm::evt_NewSvrConnected,this,&st_client_table::on_evt_NewSvrConnected,Qt::QueuedConnection);
		connect (m_pCluster,&ZP_Cluster::zp_ClusterTerm::evt_NewSvrDisconnected,this,&st_client_table::on_evt_NewSvrDisconnected,Qt::QueuedConnection);
		connect (m_pCluster,&ZP_Cluster::zp_ClusterTerm::evt_RemoteData_recieved,this,&st_client_table::on_evt_RemoteData_recieved,Qt::QueuedConnection);
		connect (m_pCluster,&ZP_Cluster::zp_ClusterTerm::evt_RemoteData_transferred,this,&st_client_table::on_evt_RemoteData_transferred,Qt::QueuedConnection);
		m_pCluster->SetNodeFactory(
					std::bind(&st_client_table::cross_svr_node_factory,
							  this,
							  _1,_2,_3)
                    );
#endif

        connect(this, &st_client_table::evt_clientClose, this, &st_client_table::on_evt_ClientDisconnected, Qt::QueuedConnection);
        m_client_nodes_size = 0;
        m_codec.reset(new CClientNode(nullptr, true));
	}
	void st_client_table::setBalanceMax(int nmax)
	{
		m_nBalanceMax = nmax;
	}

	int st_client_table::balanceMax()
	{
		return m_nBalanceMax;
	}


	int st_client_table::heartBeatingThrd()
	{
		return m_nHeartBeatingDeadThrd;
	}
	void st_client_table::setHeartBeatingThrd(int h)
	{
		m_nHeartBeatingDeadThrd = h;
	}

	//Database and disk resources
	QString st_client_table::Database_UserAcct()
	{
		return m_strDBName_useraccount;
	}
	void st_client_table::setDatabase_UserAcct(QString  s)
	{
		m_strDBName_useraccount = s;
	}
	QString st_client_table::Database_Event()
	{
		return m_strDBName_event;
	}
	void st_client_table::setDatabase_Event(QString  s)
	{
		m_strDBName_event = s;
	}
	QString st_client_table::largeFileFolder()
	{
		return m_largeFileFolder;
	}
	void st_client_table::setLargeFileFolder(QString  s)
	{
		m_largeFileFolder = s;
	}

	ZPDatabase::DatabaseResource * st_client_table::dbRes()
	{
		return m_pDatabaseRes;
	}

	st_client_table::~st_client_table()
    {

	}
	void  st_client_table::KickDeadClients()
    {
        SockNodeContainer::iterator p;
        SockNodeContainer::iterator delP;

        for (p =m_hash_sock2node.begin(); p!=m_hash_sock2node.end(); )
        {
            if((*p).second)
            {
                if((*p).second->checkHeartBeating(m_nHeartBeatingDeadThrd)) //没能移除，直接删除
                {
                    //Q_Q_EMIT evt_clientClose((*p).first);
                }
                ++p;
            }
            else
            {
                delP = p;
                ++p;
                m_hash_sock2node.erase(delP);
            }

        }
	}

    size_t st_client_table::ActiveNodes()
    {
        return m_client_nodes_size;
    }

#ifdef USE_PROTOBUF
    bool st_client_table::regisitClientUUID(CClientNode * c)
#else
    bool st_client_table::regisitClientUUID(st_clientNode_baseTrans * c)
#endif
	{
#if 0
		if (c->uuidValid()==false)
            return false;
        m_hash_uuid2node[c->uuid()] = c;
        broadcast_client_uuid(c->uuid(),true);
#endif
		return true;
	}

    NodeWkPtr st_client_table::clientNodeFromUUID(quint64 uuid)
    {
        NodeWkPtr pNode;
		if (m_hash_uuid2node.find(uuid)!=m_hash_uuid2node.end())
        {
            pNode = m_hash_uuid2node[uuid];
        }

        return pNode;
	}

    NodeWkPtr st_client_table::clientNodeFromSocket(QObject * sock)
    {
        NodeWkPtr pNode;
		if (m_hash_sock2node.find(sock)!=m_hash_sock2node.end())
        {
            pNode = m_hash_sock2node[sock];
        }
        return pNode;

	}

	//this event indicates new client encrypted.
	void st_client_table::on_evt_ClientEncrypted(QObject * clientHandle)
    {//不在此处创建任务节点，接收到数据后再创建
        return;
#if 0
		bool nHashContains = false;
        st_clientNode_baseTrans * pClientNode = 0;
		nHashContains = (m_hash_sock2node.find(clientHandle)!=m_hash_sock2node.end())?true:false;
		if (false==nHashContains)
		{
			st_clientNode_baseTrans * pnode = new st_clientNodeAppLayer(this,clientHandle,0);
			//using queued connection of send and revieve;
            connect (pnode,&st_clientNode_baseTrans::evt_SendDataToClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_SendDataToClient,Qt::QueuedConnection);
            connect (pnode,&st_clientNode_baseTrans::evt_close_client,m_pThreadEngine,&ZPNetwork::zp_net_Engine::KickClients,Qt::QueuedConnection);
			m_hash_sock2node[clientHandle] = pnode;
			nHashContains = true;
            pClientNode = pnode;
		}
		else
		{
			pClientNode =  m_hash_sock2node[clientHandle];
        }
		assert(nHashContains!=0 && pClientNode !=0);
#endif
	}

	//this event indicates new client connected.
    void  st_client_table::on_evt_NewClientConnected(QObject * clientHandle, QByteArray datablock)
    {
#ifdef USE_PROTOBUF
        m_codec->resetNode();
        m_codec->pushNewData(datablock);
        m_codec->run();
        if(!m_codec->uuidValid())
        {
            qWarning() << __FUNCTION__ << "Received data error" << datablock.length();
            return;
        }

        bool foundUuid = false;
        NodePtr pNode;
        foundUuid = m_hash_uuid2node.find(m_codec->uuid()) != m_hash_uuid2node.end();
        if(foundUuid)
        {
            qWarning() << m_codec->uuid() << "exists";
            return;
        }
        pNode = CGarbageCollector::Instance()->findNodeNoactive(m_codec->uuid());
        if(pNode != nullptr)
        {
            pNode->setClientSock(((CAsioTcpSocket*)clientHandle)->shared_from_this());
        }
        else
        {
            pNode = CGarbageCollector::Instance()->nodeResumeRabish();
            if(pNode)
            {
                pNode->setClientSock(((CAsioTcpSocket*)clientHandle)->shared_from_this());
            }
            else
                pNode.reset(new CClientNode(((CAsioTcpSocket*)clientHandle)->shared_from_this()));
        }
        //using queued connection of send and revieve;
        connect (pNode.get(),&CClientNode::evt_SendDataToClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_SendDataToClient,Qt::QueuedConnection);
        connect (pNode.get(),&CClientNode::evt_CloseClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::KickClients,Qt::QueuedConnection);

        m_hash_sock2node[clientHandle] = pNode;
        m_hash_uuid2node[m_codec->uuid()] = pNode;
        int nblocks =  pNode->pushNewData(datablock);
        if (nblocks<=1)
            m_pTaskEngine->pushTask(pNode.get());
        Q_EMIT evt_AddNewClientOk(clientHandle);
        m_client_nodes_size = m_hash_sock2node.size();
#else
        if(datablock.length() < 16) //数据包太短，格式不正确
        {
            qWarning() << __FUNCTION__ << "packet format error" << datablock.length();
            return;
        }
        bool foundUuid = false;
        quint64 source_id = 0;
        boost::shared_ptr<st_clientNode_baseTrans> pNode;

        source_id = st_packet_tool::getUuid(datablock);
        foundUuid = m_hash_uuid2node.find(source_id) != m_hash_uuid2node.end();
        if(foundUuid)
        {
            return;
        }
        pNode = CGarbageCollector::Instance()->findNodeNoactive(source_id);
        if(pNode != nullptr)
        {
            pNode->setClientSock(clientHandle);
        }
        else
        {
            pNode = CGarbageCollector::Instance()->nodeResumeRabish();
            if(pNode)
            {
                pNode->setClientSock(clientHandle);
            }
            else
                pNode.reset(new st_clientNodeAppLayer(this, clientHandle));
        }
        //using queued connection of send and revieve;
        connect (pNode.get(),&st_clientNode_baseTrans::evt_SendDataToClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_SendDataToClient,Qt::QueuedConnection);
        connect (pNode.get(),&st_clientNode_baseTrans::evt_CloseClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::KickClients,Qt::QueuedConnection);

        m_hash_sock2node[clientHandle] = pNode;
        m_hash_uuid2node[source_id] = pNode;

        int nblocks =  pNode->pushNewData(datablock);
        if (nblocks<=1)
            m_pTaskEngine->pushTask(pNode.get());
        Q_EMIT evt_AddNewClientOk(clientHandle);
        m_client_nodes_size = m_hash_sock2node.size();
#endif
	}

	//this event indicates a client disconnected.
	void  st_client_table::on_evt_ClientDisconnected(QObject * clientHandle)
    {
		bool nHashContains  = false;
        NodePtr pClientNode;

        nHashContains = (m_hash_sock2node.find(clientHandle)!=m_hash_sock2node.end())?true:false;
		if (nHashContains)
			pClientNode =  m_hash_sock2node[clientHandle];
		if (pClientNode)
        {
            if (pClientNode->uuidValid())
            {
                //This is important. some time m_hash_sock2node and m_hash_uuid2node, same uuid has different socket.
                if (m_hash_uuid2node.find(pClientNode->uuid())!=m_hash_uuid2node.end())
                    if (m_hash_uuid2node[pClientNode->uuid()].lock().get() == pClientNode.get())
                    {
                        m_hash_uuid2node.erase(pClientNode->uuid());
                        broadcast_client_uuid(pClientNode->uuid(),false);
                    }
            }
            CGarbageCollector::Instance()->nodePutInNoactive(pClientNode);
            m_hash_sock2node.erase(clientHandle);
            pClientNode->bTermSet = true;
#ifdef USE_PROTOBUF
            disconnect (pClientNode.get(),&CClientNode::evt_SendDataToClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_SendDataToClient);
            disconnect (pClientNode.get(),&CClientNode::evt_CloseClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::KickClients);
#else
            disconnect (pClientNode.get(),&st_clientNode_baseTrans::evt_SendDataToClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::evt_SendDataToClient);
            disconnect (pClientNode.get(),&st_clientNode_baseTrans::evt_CloseClient,m_pThreadEngine,&ZPNetwork::zp_net_Engine::KickClients);
#endif

			//qDebug()<<QString("%1(ref %2) Node Push in queue.\n").arg((unsigned int)pClientNode).arg(pClientNode->ref());
        }
        m_client_nodes_size = m_hash_sock2node.size();
	}

	//some data arrival
	void  st_client_table::on_evt_Data_recieved(QObject *  clientHandle,QByteArray  datablock )
    {
		//Push Clients to nodes if it is not exist
        bool nHashContains = false;
        nHashContains = (m_hash_sock2node.find(clientHandle) != m_hash_sock2node.end());

        if (false==nHashContains)
        {
            return;
        }

        NodePtr pClientNode;

        pClientNode =  m_hash_sock2node[clientHandle];
        //assert(nHashContains!=0 && pClientNode !=0);

        int nblocks =  pClientNode->pushNewData(datablock);
        if (nblocks > 0)
            m_pTaskEngine->pushTask(pClientNode.get());
	}

	//a block of data has been successfuly sent
	void  st_client_table::on_evt_Data_transferred(QObject *   /*clientHandle*/,qint64 /*bytes sent*/)
	{

	}

	//this event indicates new svr successfully hand-shaked.
	void st_client_table::on_evt_NewSvrConnected(QString  svrHandle)
	{
#if 0
		//Send All Client UUIDs to new Svr
		m_hash_mutex.lock();
		QList<quint32> uuids;
		for(std::unordered_map<quint32,st_clientNode_baseTrans *>::iterator p =  m_hash_uuid2node.begin();
			p!=m_hash_uuid2node.end();p++)
			uuids.push_back((*p).first);
		int nNodeSz = uuids.size();
		if (nNodeSz>0)
		{
			int nMsgLen = sizeof(EXAMPLE_CROSSSVR_MSG::tag_msgHearder) +  nNodeSz * sizeof(quint32);
			QByteArray array(nMsgLen,0);
			EXAMPLE_CROSSSVR_MSG * pMsg = (EXAMPLE_CROSSSVR_MSG *) array.data();
			pMsg->header.Mark = 0x4567;
			pMsg->header.version = 1;
			pMsg->header.messageLen = nNodeSz * sizeof(quint32);
			pMsg->header.mesageType = 0x01;
			int ct = -1;
			foreach (quint32 uuid,uuids)
				pMsg->payload.uuids[++ct] = uuid;
			m_pCluster->SendDataToRemoteServer(svrHandle,array);
		}
		m_hash_mutex.unlock();
        Q_EMIT evt_Message(this,tr("Send Initial UUIDs to Remote Svr:") + svrHandle);
#endif
	}
    void st_client_table::broadcast_client_uuid(quint64 uuid, bool bActive)
	{
#if 0
		QStringList svrs = m_pCluster->SvrNames();
		if (svrs.empty()==false)
		{
			int nMsgLen = sizeof(EXAMPLE_CROSSSVR_MSG::tag_msgHearder) +  sizeof(quint32);
			QByteArray array(nMsgLen,0);
			EXAMPLE_CROSSSVR_MSG * pMsg = (EXAMPLE_CROSSSVR_MSG *) array.data();
			pMsg->header.Mark = 0x4567;
			pMsg->header.version = 1;
			pMsg->header.messageLen = sizeof(quint32);
			pMsg->header.mesageType = bActive==true?0x01:0x02;
			pMsg->payload.uuids[0] = uuid;
			foreach (QString svr,svrs)
				m_pCluster->SendDataToRemoteServer(svr,array);
		}
#endif
	}
    bool st_client_table::SendToNode(quint64 uuid, QByteArray  msg)
	{
        bool bres = false;
		if (m_hash_uuid2node.find(uuid)!=m_hash_uuid2node.end())
        {
            NodePtr pAppLayer = m_hash_uuid2node[uuid].lock();
			if (pAppLayer)
			{
				this->m_pThreadEngine->SendDataToClient(pAppLayer->sock(),msg);
				bres = true;
			}
        }
        //Q_EMIT evt_Message(this,tr("Recieved remote user-data to uuid:%1,DATA:%2").arg(uuid).arg(QString("HEX")+QString(msg.toHex())));
		return bres;
	}

	//this event indicates a client disconnected.
	void st_client_table::on_evt_NewSvrDisconnected(QString  svrHandle)
	{
		//remove all client-maps belongs to this server.
		this->cross_svr_del_uuids(svrHandle,NULL,0);
        qDebug() << "Svr DisConnected. " + svrHandle;
	}

	//some data arrival
	void st_client_table::on_evt_RemoteData_recieved(QString  svrHandle,QByteArray  array )
	{
        qDebug() << tr("Recieved %1 bytes Msg from ").arg(array.length()) + svrHandle;
	}

	//a block of data has been successfuly sent
	void st_client_table::on_evt_RemoteData_transferred(QObject *  /*svrHandle*/,qint64 /*bytes sent*/)
	{

	}
	ZP_Cluster::zp_ClusterNode * st_client_table::cross_svr_node_factory(
			ZP_Cluster::zp_ClusterTerm * pTerm,
			QObject * psock,
			QObject * parent)
	{
#if 0
		st_cross_svr_node * pNode = new st_cross_svr_node(pTerm,psock,parent);
		pNode->setClientTable(this);
		//connect (pNode,&st_cross_svr_node::evt_SendToNode,this,&st_client_table::SendToNode,Qt::QueuedConnection);
		return pNode;
#endif
        return NULL;
	}
	//reg new uuids in m_hash_remoteClient2SvrName
    void st_client_table::cross_svr_add_uuids(QString  svrname, quint64 *pUUIDs, int nUUIDs)
	{
		m_mutex_cross_svr_map.lock();
		for (int i=0;i<nUUIDs;i++)
			m_hash_remoteClient2SvrName[pUUIDs[i]] = svrname;
		m_mutex_cross_svr_map.unlock();
        qDebug() << tr("Recieved remote %1 client uuid(s) from svr ").arg(nUUIDs) + svrname;
	}

	//del uuids in m_hash_remoteClient2SvrName, pUUIDs =0 means del all uuids belong to svrname
    void st_client_table::cross_svr_del_uuids(QString  svrname,quint64 * pUUIDs , int nUUIDs)
	{
		m_mutex_cross_svr_map.lock();
		if (pUUIDs==NULL)
		{
            QList<quint64> keys;
            for(std::unordered_map<quint64,QString>::iterator p =
				m_hash_remoteClient2SvrName.begin();
				p!=m_hash_remoteClient2SvrName.end();p++)
			{
				if ((*p).second == svrname )
					keys.push_back((*p).first);
			}
            foreach (quint64 key, keys)
			{
				m_hash_remoteClient2SvrName.erase(key);
			}
		}
		else
		{
			for (int i=0;i<nUUIDs;i++)
				m_hash_remoteClient2SvrName.erase(pUUIDs[i]);
		}
		m_mutex_cross_svr_map.unlock();
        qDebug() << tr("Removed remote %1 client uuid(s) from svr ").arg(nUUIDs) + svrname;
	}
	void st_client_table::cross_svr_send_data(QString  svrname,QByteArray  arr)
	{
#if 0
		int nMsgLen = sizeof(EXAMPLE_CROSSSVR_MSG::tag_msgHearder);
		QByteArray array(nMsgLen,0);
		EXAMPLE_CROSSSVR_MSG * pMsg = (EXAMPLE_CROSSSVR_MSG *) array.data();
		pMsg->header.Mark = 0x4567;
		pMsg->header.version = 1;
		pMsg->header.messageLen = arr.size();
		pMsg->header.mesageType = 0x03;
		array.append(arr);
		m_pCluster->SendDataToRemoteServer(svrname,array);
#endif
	}

    QString  st_client_table::cross_svr_find_uuid(quint64 uuid)
	{
		QString svr = "";
		m_mutex_cross_svr_map.lock();
		if (m_hash_remoteClient2SvrName.find(uuid)!=m_hash_remoteClient2SvrName.end())
			svr = m_hash_remoteClient2SvrName[uuid];
		m_mutex_cross_svr_map.unlock();
		return svr;
	}

	bool st_client_table::NeedRedirect(quint8 bufAddresses[/*64*/],quint16 * pnPort)
    {
#if 0
		if (m_pCluster->clientNums()<m_nBalanceMax)
			return false;
		QString strServerName = m_pCluster->minPayloadServer(bufAddresses,pnPort);
		if (strServerName==m_pCluster->name())
            return false;
#endif
		return true;
    }
}

