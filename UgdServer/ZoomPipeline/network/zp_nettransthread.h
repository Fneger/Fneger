/**
 * @brief class zp_netTransThread by goldenhawking, 2013,2014
 */
#ifndef ZP_NETTRANSTHREAD_H
#define ZP_NETTRANSTHREAD_H

#include <QObject>
#include <QList>
#include <QAbstractSocket>
#include <QMutex>
#include <unordered_map>
#include <QSet>
#include <QList>
#include <boost/shared_ptr.hpp>
#include "csocketsession.h"

class CAsioTcpSocket;
typedef boost::weak_ptr<CAsioTcpSocket> TcpSocketWkPtr;
typedef boost::shared_ptr<CAsioTcpSocket> TcpSocketPtr;
typedef std::unordered_map<qint64, TcpSocketPtr> TcpSocketContainer;
typedef std::unordered_map<qint64, TcpSocketWkPtr> WkTcpSocketContainer;

namespace ZPNetwork{
	class zp_net_Engine;

	/**
	 * @brief class zp_netTransThread is a QObject-derived object class.
	 * Objects of this type will be binded to a QThread, in which TCP transfer
	 * will work
	 */
	class zp_netTransThread : public QObject
	{
		Q_OBJECT
	public:
        explicit zp_netTransThread(zp_net_Engine * pThreadPool,int nPayLoad = 4096,QObject *parent = 0);
        ~zp_netTransThread();
        size_t CurrentClients();
		void SetPayload(int nPayload);
		bool isActive();

		bool CanExit();
		bool SSLConnection();
		void SetSSLConnection(bool bssl);
        size_t RabishCanSockets();
        size_t NewClientSockets();
		//Size of the RubbishCan
        static int RUBBISH_CAN_SIZE;


	private:
        static const int S_RABISH_CAN_TIMEOUT = 20;
        static const int S_DEAD_NEW_CLIENT_KEEP_TIME = 200;
		bool m_bActivated;
		bool m_bSSLConnection;
		//sending buffer, hold byteArraies.
		std::unordered_map<QObject *,QList<QByteArray> > m_buffer_sending;

		std::unordered_map<QObject *,QList<qint64> > m_buffer_sending_offset;
		//The socket and the connection-direction, 0 is passive, 1 is postive.
        TcpSocketContainer m_clientList;
        volatile size_t m_clients_size;
		int m_nPayLoad;
        //QMutex m_mutex_protect;
        zp_net_Engine * m_pThreadPool;
        //QMutex m_mutex_rabish_can;
        volatile size_t m_rabish_can_size;

        //QMutex m_new_clients_mutex;
        volatile size_t m_new_clients_size;
        WkTcpSocketContainer m_new_clients;

        //添加删除未创建任务节点的客户端
        void add_new_client(const TcpSocketPtr &newClient);
        void remove_new_client(CAsioTcpSocket *delClient);
        //添加删除客户端
        void add_client(const TcpSocketPtr &newClient);
        void remove_client(CAsioTcpSocket *delClient);
	public slots:
        //以下槽函数必须以QueuedConnection连接
		//This slot dealing with multi-thread client socket accept.
        void incomingConnection(QObject * threadid, session_ptr session);
		//This slot dealing with possive connecting-to method.
		void startConnection(QObject * threadid,const QHostAddress & addr, quint16 port, quint64 extraData);
		//sending dtarray to objClient. dtarray will be pushed into m_buffer_sending
		void SendDataToClient(QObject * objClient,QByteArray   dtarray);
		//Set terminate mark, the thread will quit after last client quit.
		void Deactivate();
		//terminate this thread immediately
		void DeactivateImmediately(zp_netTransThread *);
		//Kick all clients .
		void KickAllClients(zp_netTransThread *);
		//Kick client.
		void KickClient(QObject *);
        void KickRabishCanTimeOutObj();
        void AddNewClientOk(QObject *pSock);
        void EmptyRabishCan(QObject *pTransObj);

	protected slots:
		//when client closed, this slot will be activated.
        void client_closed();
        void new_data_recieved(const QByteArray &data);
		void some_data_sended(qint64);
        void displayError(const QString &erro);
		//Plain Connected
		void on_connected();
		//SSL Encrypted started
		void on_encrypted();
    Q_SIGNALS:
        void evt_SocketError(QObject * senderSock ,const QString &erro, quint64 extraData);
        void evt_NewClientConnected(QObject * client, QByteArray ba, quint64 extraData);
		void evt_ClientEncrypted(QObject * client, quint64 extraData);
		void evt_ClientDisconnected(QObject * client, quint64 extraData);
		void evt_Data_recieved(QObject * ,QByteArray   , quint64 extraData);
		void evt_Data_transferred(QObject * client,qint64, quint64 extraData);
	};
}
#endif // ZP_NETTRANSTHREAD_H
