#include "zp_nettransthread.h"
#include "ssl_config.h"
#include <QTcpSocket>
#if (ZP_WANTSSL!=0)
#include <QSslSocket>
#endif
#include <assert.h>
#include <QDebug>
#include <QCoreApplication>
#include <QHostAddress>
#include "zp_net_threadpool.h"
#include <QMutex>
#include "casiotcpsocket.h"
#include "cgarbagecollector.h"

//Trans st
QMutex g_mutex_sta;
quint64 g_bytesRecieved = 0;
quint64 g_bytesSent = 0;
quint64 g_secRecieved = 0;
quint64 g_secSent = 0;

namespace ZPNetwork{
    int zp_netTransThread::RUBBISH_CAN_SIZE = 256;

    zp_netTransThread::zp_netTransThread(zp_net_Engine *pThreadPool,int nPayLoad,QObject *parent) :
		QObject(parent)
      ,m_pThreadPool(pThreadPool)
	{
		m_nPayLoad = nPayLoad;
		m_bActivated = true;
        m_bSSLConnection = false;
        assert(m_nPayLoad>=256 && m_nPayLoad<=16*1024*1024);
        m_new_clients_size = 0;
        m_clients_size = 0;
        m_rabish_can_size = 0;
	}
    zp_netTransThread::~zp_netTransThread()
    {

    }
    void zp_netTransThread::EmptyRabishCan(QObject *pTransObj)
	{
        if(pTransObj != this)
            return;
        m_rabish_can_size = 0;
	}

    size_t zp_netTransThread::RabishCanSockets()
    {
        return m_rabish_can_size;
    }

    size_t zp_netTransThread::NewClientSockets()
    {
        return m_new_clients_size;
    }

	bool zp_netTransThread::isActive()
	{
		return m_bActivated;
	}
	bool zp_netTransThread::SSLConnection()
	{
		return m_bSSLConnection ;
	}
	void zp_netTransThread::SetSSLConnection(bool bssl)
	{
		m_bSSLConnection = bssl;
	}
	void zp_netTransThread::Deactivate()
	{
		m_bActivated = false;
    }
	/**
	 * @brief return howmany clients holded by this zp_netTransThread
	 *
	 * @return int the clients count
	 */
    size_t zp_netTransThread::CurrentClients()
    {
        return m_clients_size;
	}
	/**
	 * @brief this slot recieves evt_DeactivateImmediately message,
	 * if this message is sent to this object, a "KickAllClients"
	 * method will be called.
	 *
	 * @param ptr
	 */
	void zp_netTransThread::DeactivateImmediately(zp_netTransThread * ptr)
	{
		if (ptr!=this)
			return;
		m_bActivated = false;
		this->KickAllClients(ptr);
	}

	/**
	 * @brief set the payload of this object. data large than nPayload will be
	 * cutted into pieces, each piece is nPayload bytes. the last piece may be
	 * shorter than nPayload.
	 *
	 * @param nPayload bytes a signal block contains .
	 */
	void zp_netTransThread::SetPayload(int nPayload)
	{
		m_nPayLoad = nPayload;
		assert(m_nPayLoad>=256 && m_nPayLoad<=16*1024*1024);
    }

    void zp_netTransThread::add_new_client(const boost::shared_ptr<CAsioTcpSocket> &newClient)
    {
        qint64 nId = (qint64)newClient.get();
        m_new_clients[nId] = newClient;
        m_new_clients_size = m_new_clients.size();
    }

    void zp_netTransThread::remove_new_client(CAsioTcpSocket *delClient)
    {
        qint64 nId = (qint64)delClient;
        if(m_new_clients.find(nId) != m_new_clients.end())
            m_new_clients.erase(nId);
        m_new_clients_size = m_new_clients.size();
    }

    void zp_netTransThread::add_client(const boost::shared_ptr<CAsioTcpSocket> &newClient)
    {
        qint64 nId = (qint64)newClient.get();
        m_clientList[nId] = newClient;
        m_clients_size = m_clientList.size();
    }
    void zp_netTransThread::remove_client(CAsioTcpSocket *delClient)
    {
        remove_new_client(delClient);
        qint64 nId = (qint64)delClient;
        if(m_clientList.find(nId) != m_clientList.end())
        {
            boost::shared_ptr<CAsioTcpSocket> pSock = m_clientList[nId];
            CGarbageCollector::Instance()->sockPutInTrash(pSock);
            m_clientList.erase(nId);
            m_buffer_sending.erase(delClient);
            m_buffer_sending_offset.erase(delClient);
        }
        m_clients_size = m_clientList.size();
    }

    void zp_netTransThread::KickRabishCanTimeOutObj()
    {
        qint64 currSec = QDateTime::currentSecsSinceEpoch();
        //m_new_clients_mutex.lock();
        if(m_new_clients.size() > 0)
        {
            std::unordered_map<qint64, boost::weak_ptr<CAsioTcpSocket>>::iterator it;
            for (it =m_new_clients.begin(); it!=m_new_clients.end();)
            {
                boost::shared_ptr<CAsioTcpSocket> pSock(it->second.lock());
                if(pSock)
                {
                    if(currSec - pSock->activeTime() > S_DEAD_NEW_CLIENT_KEEP_TIME)
                    {
                        ++it;
                        m_new_clients.erase((qint64)pSock.get());
                        KickClient(pSock.get());
                    }
                    else
                        ++it;
                }
                else
                {
                    ++it;
                    m_new_clients.erase((qint64)pSock.get());
                }
            }
        }
        //m_new_clients_mutex.unlock();
    }

	/**
	 * @brief This slot dealing with multi-thread client socket accept.
	 * accepy works start from zp_netListenThread::m_tcpserver, end with this method.
	 * the socketDescriptor is delivered from zp_netListenThread(a Listening thread)
	 *  to zp_net_Engine(Normally in main-gui thread), and then zp_netTransThread.
	 *
	 * @param threadid if threadid is not equal to this object, this message is just omitted.
	 * @param socketDescriptor socketDescriptor for incomming client.
	 */
    void zp_netTransThread::incomingConnection(QObject * threadid,session_ptr session)
	{
		if (threadid!=this)
            return;
#if (ZP_WANTSSL!=0)
		if (m_bSSLConnection)
            sock_client =  new QAsioTcpsocket(pSession);
		else
            sock_client =  new QAsioTcpsocket(pSession);
#else
        boost::shared_ptr<CAsioTcpSocket> sock_client;
        sock_client = CGarbageCollector::Instance()->sockResumeRabish();
        if(!sock_client)
            sock_client = boost::make_shared<CAsioTcpSocket>(session);
        else
        {
            sock_client->setSession(session);
            sock_client->setIsNewClient(true);
        }
        sock_client->init();
#endif
		if (sock_client)
		{


			//Initial content
            if (true /*==sock_client->setSocketDescriptor(socketDescriptor)*/)
			{
                connect(sock_client.get(), &CAsioTcpSocket::sentReadData,this, &zp_netTransThread::new_data_recieved,Qt::QueuedConnection);
                connect(sock_client.get(), &CAsioTcpSocket::disConnected,this,&zp_netTransThread::client_closed,Qt::QueuedConnection);
                connect(sock_client.get(), &CAsioTcpSocket::erroString,this,&zp_netTransThread::displayError,Qt::QueuedConnection);
                connect(sock_client.get(), &CAsioTcpSocket::bytesWritten, this, &zp_netTransThread::some_data_sended,Qt::QueuedConnection);

                add_new_client(sock_client);
                add_client(sock_client);

#if (ZP_WANTSSL!=0)
				if (m_bSSLConnection)
				{
					QSslSocket * psslsock = qobject_cast<QSslSocket *>(sock_client);
					assert(psslsock!=NULL);
					QString strCerPath =  QCoreApplication::applicationDirPath() + "/svr_cert.pem";
					QString strPkPath =  QCoreApplication::applicationDirPath() + "/svr_privkey.pem";
					psslsock->setLocalCertificate(strCerPath);
					psslsock->setPrivateKey(strPkPath);
					connect(psslsock, &QSslSocket::encrypted,this, &zp_netTransThread::on_encrypted,Qt::QueuedConnection);
					psslsock->startServerEncryption();
				}
#endif
                sock_client->do_start();
                //qDebug()<<sock_client->peerIp() <<
                //		  sock_client->peerPort()  <<tr("(%1)..Accepted.").arg((quint64)sock_client);
#if 0
                quint64 extraData = 0;
                if (m_extraData.contains(sock_client))
                    extraData = m_extraData[sock_client];

                Q_EMIT evt_NewClientConnected(sock_client,extraData);
#endif
                //Q_EMIT evt_Message(sock_client,"Info>" +  QString(tr("Client Accepted.")));
            }
        }
	}

	/**
	 * @brief This method will create a socket, and directly connect to destion address.
	 *
	 * @param threadid if threadid is not equal to this object, this message is just omitted.
	 * @param addr address to which the socket should be connected.
	 * @param port port to which the socket should be connected.
	 */
	void zp_netTransThread::startConnection(QObject * threadid,const QHostAddress & addr, quint16 port, quint64 extraData)
	{
		if (threadid!=this)
			return;
#if 0
        QTcpSocket * sock_client = 0;
#if (ZP_WANTSSL!=0)
		if (m_bSSLConnection)
			sock_client =  new QSslSocket(this);
		else
			sock_client =  new QTcpSocket(this);
#else
        sock_client =  new QTcpSocket(this);
#endif
		if (sock_client)
        {
#if (ZP_WANTSSL!=0)
			if (m_bSSLConnection==true)
			{

				QSslSocket * psslsock = qobject_cast<QSslSocket *>(sock_client);
				assert(psslsock!=NULL);
				QString strCerPath =  QCoreApplication::applicationDirPath() + "/ca_cert.pem";
				QList<QSslCertificate> lstCas = QSslCertificate::fromPath(strCerPath);
				psslsock->setCaCertificates(lstCas);

//				connect(sock_client, &QTcpSocket::readyRead,this,&zp_netTransThread::new_data_recieved,Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::disconnected,this,&zp_netTransThread::client_closed,Qt::QueuedConnection);
//				connect(sock_client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)),Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::bytesWritten, this,&zp_netTransThread::some_data_sended,Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::connected,this, &zp_netTransThread::on_connected,Qt::QueuedConnection);
				connect(psslsock, &QSslSocket::encrypted,this, &zp_netTransThread::on_encrypted,Qt::QueuedConnection);
				m_mutex_protect.lock();
				m_clientList.insert(sock_client);
				m_mutex_protect.unlock();

				psslsock->connectToHostEncrypted(addr.toString(),port);
			}
			else
			{
//				connect(sock_client, &QTcpSocket::readyRead,this, &zp_netTransThread::new_data_recieved,Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::disconnected,this,&zp_netTransThread::client_closed,Qt::QueuedConnection);
//				connect(sock_client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)),Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::bytesWritten, this,&zp_netTransThread::some_data_sended,Qt::QueuedConnection);
				connect(sock_client, &QTcpSocket::connected,this, &zp_netTransThread::on_connected,Qt::QueuedConnection);
				m_mutex_protect.lock();
				m_clientList.insert(sock_client);
				m_mutex_protect.unlock();
				sock_client->connectToHost(addr,port);

			}
#else
            //connect(sock_client, &QTcpSocket::readyRead,this, &zp_netTransThread::new_data_recieved,Qt::QueuedConnection);
			connect(sock_client, &QTcpSocket::disconnected,this,&zp_netTransThread::client_closed,Qt::QueuedConnection);
            //connect(sock_client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)),Qt::QueuedConnection);
			connect(sock_client, &QTcpSocket::bytesWritten, this,&zp_netTransThread::some_data_sended,Qt::QueuedConnection);
			connect(sock_client, &QTcpSocket::connected,this, &zp_netTransThread::on_connected,Qt::QueuedConnection);
			m_mutex_protect.lock();
            m_clientList[sock_client] = 0;
			m_mutex_protect.unlock();
			sock_client->connectToHost(addr,port);
#endif
		}
		else
			assert(false);
#endif
	}
	void zp_netTransThread::on_connected()
	{
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(sender());
        //Q_EMIT evt_NewClientConnected(pSock,extraData);
        qDebug() << QString("%1").arg((qint64)pSock) << QString(tr("Client connected."));
	}

	void zp_netTransThread::on_encrypted()
	{
        QTcpSocket * pSock = qobject_cast<QTcpSocket*>(sender());
        Q_EMIT evt_ClientEncrypted(pSock,0);
        qDebug() << QString("%1").arg((qint64)pSock) << QString(tr("Client Encrypted."));
    }

	void zp_netTransThread::client_closed()
    {
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(sender());
        qint64 nId = (qint64)sender();
        bool isContains = m_clientList.find(nId) != m_clientList.end();

        if (isContains)
        {

#if (ZP_WANTSSL!=0)
			if (m_bSSLConnection)
			{
				QSslSocket * psslsock = qobject_cast<QSslSocket *>(pSock);
				if (psslsock)
					disconnect(psslsock, &QSslSocket::encrypted,this, &zp_netTransThread::on_encrypted);
			}
#endif
            disconnect(pSock, &CAsioTcpSocket::sentReadData,this, &zp_netTransThread::new_data_recieved);
            disconnect(pSock, &CAsioTcpSocket::disConnected,this,&zp_netTransThread::client_closed);
            disconnect(pSock, &CAsioTcpSocket::erroString,this,&zp_netTransThread::displayError);
            disconnect(pSock, &CAsioTcpSocket::bytesWritten, this, &zp_netTransThread::some_data_sended);
            disconnect(pSock, &CAsioTcpSocket::connected,this, &zp_netTransThread::on_connected);

			m_buffer_sending.erase(pSock);
            m_buffer_sending_offset.erase(pSock);
            pSock->disconnectFromHost();
            remove_client(pSock);
			//pSock->abort();
            Q_EMIT evt_ClientDisconnected(pSock,0);
            qDebug() << QString("%1").arg((qint64)pSock) << QString(tr("Client Closed."));
        }
	}
    void zp_netTransThread::new_data_recieved(const QByteArray & data)
    {
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(sender());
		if (pSock)
        {

            //quint64 extraData = 0;
            //if (m_extraData.contains(pSock)) extraData = m_extraData[pSock];

            QByteArray array = data;//pSock->readAll();
			int sz = array.size();
			g_mutex_sta.lock();
			g_bytesRecieved +=sz;
			g_secRecieved += sz;
            g_mutex_sta.unlock();
            if(!pSock->isNewClient())
            {
                Q_EMIT evt_Data_recieved(pSock,array,0);
            }
            else
            {
                pSock->setIsNewClient(false);
                Q_EMIT evt_NewClientConnected(pSock,array, 0);
            }
		}
	}

    void zp_netTransThread::AddNewClientOk(QObject *pSock)
    {
        remove_new_client((CAsioTcpSocket*)pSock);
    }
	/**
	 * @brief this slot will be called when internal socket successfully
	 * sent some data. in this method, zp_netTransThread object will check
	 * the sending-queue, and send more data to buffer.
	 *
	 * @param wsended
	 */
	void zp_netTransThread::some_data_sended(qint64 wsended)
    {
		g_mutex_sta.lock();
		g_bytesSent +=wsended;
		g_secSent += wsended;
		g_mutex_sta.unlock();
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(sender());
		if (pSock)
        {
            Q_EMIT evt_Data_transferred(pSock,wsended,0);
			QList<QByteArray> & list_sock_data = m_buffer_sending[pSock];
			QList<qint64> & list_offset = m_buffer_sending_offset[pSock];
			while (list_sock_data.empty()==false)
			{
				QByteArray & arraySending = *list_sock_data.begin();
				qint64 & currentOffset = *list_offset.begin();
				qint64 nTotalBytes = arraySending.size();
				assert(nTotalBytes>=currentOffset);
                qint64 nBytesWritten = qMin((int)(nTotalBytes-currentOffset),m_nPayLoad);
                pSock->write(arraySending.constData()+currentOffset,nBytesWritten);
				currentOffset += nBytesWritten;
				if (currentOffset>=nTotalBytes)
				{
					list_offset.pop_front();
					list_sock_data.pop_front();
				}
				else
					break;
			}
		}
	}
    void zp_netTransThread::displayError(const QString & erro)
    {
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(sender());
		if (pSock)
        {
            Q_EMIT evt_SocketError(pSock,erro,0);
#if (ZP_WANTSSL!=0)
			if (m_bSSLConnection)
			{
				QSslSocket * psslsock = qobject_cast<QSslSocket *>(pSock);
				if (psslsock)
					disconnect(psslsock, &QSslSocket::encrypted,this, &zp_netTransThread::on_encrypted);
			}
#endif
            disconnect(pSock, &CAsioTcpSocket::sentReadData,this, &zp_netTransThread::new_data_recieved);
            disconnect(pSock, &CAsioTcpSocket::disConnected,this,&zp_netTransThread::client_closed);
            disconnect(pSock, &CAsioTcpSocket::erroString,this,&zp_netTransThread::displayError);
            disconnect(pSock, &CAsioTcpSocket::bytesWritten, this, &zp_netTransThread::some_data_sended);
            disconnect(pSock, &CAsioTcpSocket::connected,this, &zp_netTransThread::on_connected);
            pSock->disconnectFromHost();
            Q_EMIT evt_ClientDisconnected(pSock,0);
            qDebug() << QString("%1").arg((qint64)pSock) << QString(tr("Client Error, Closed."));
            //pSock->disconnectFromHost();
            remove_client(pSock);
        }
	}

	void zp_netTransThread::SendDataToClient(QObject * objClient,QByteArray   dtarray)
    {
        qint64 nId = (qint64)objClient;
        if (m_clientList.find(nId) == m_clientList.end())
        {
            return;
        }
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(objClient);
        if (pSock && dtarray.size())
		{
			QList<QByteArray> & list_sock_data = m_buffer_sending[pSock];
			QList<qint64> & list_offset = m_buffer_sending_offset[pSock];
			if (list_sock_data.empty()==true)
			{
                qint64 bytesWritten = qMin(dtarray.size(),m_nPayLoad);
                pSock->write(dtarray.constData(),bytesWritten);
				if (bytesWritten < dtarray.size())
				{
					list_sock_data.push_back(dtarray);
					list_offset.push_back(bytesWritten);
				}
			}
			else
			{
				list_sock_data.push_back(dtarray);
				list_offset.push_back(0);
			}
		}
	}

	void zp_netTransThread::KickAllClients(zp_netTransThread * ptr)
	{
		if (ptr!=this)
            return;
        std::unordered_map<qint64, boost::shared_ptr<CAsioTcpSocket>>::iterator it;
        for(it = m_clientList.begin(); it != m_clientList.end(); ++it)
        {
            CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>((*it).second.get());
            if (pSock)
            {
                pSock->disconnectFromHost();
            }
        }

        EmptyRabishCan(this);
	}

	void zp_netTransThread::KickClient(QObject * objClient)
    {
        qint64 nId = (qint64)objClient;
        if (m_clientList.find(nId) == m_clientList.end())
        {
			return;
        }
        CAsioTcpSocket * pSock = qobject_cast<CAsioTcpSocket*>(objClient);

		if (pSock)
		{
			pSock->disconnectFromHost();
        }
	}

	bool zp_netTransThread::CanExit()
	{
		if (m_bActivated==true)
			return false;
		if (CurrentClients())
			return false;
		return true;
	}
}
