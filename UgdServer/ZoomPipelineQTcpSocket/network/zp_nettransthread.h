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
		QList <QObject *> clientsList();
		int CurrentClients();
		void SetPayload(int nPayload);
		bool isActive();

		bool CanExit();
		bool SSLConnection();
		void SetSSLConnection(bool bssl);

		//RubbishCan Functions
		void Empty_RabishCan();
		//Size of the RubbishCan
		static int RUBBISH_CAN_SIZE;

	private:
		bool m_bActivated;
		bool m_bSSLConnection;
		//sending buffer, hold byteArraies.
		std::unordered_map<QObject *,QList<QByteArray> > m_buffer_sending;

		std::unordered_map<QObject *,QList<qint64> > m_buffer_sending_offset;
		//The socket and the connection-direction, 0 is passive, 1 is postive.
		QSet<QObject*> m_clientList;
		int m_nPayLoad;
		QMutex m_mutex_protect;
		zp_net_Engine * m_pThreadPool;
		//Rabish Can
		QList<QObject *> m_rabish_can;
		QSet<QObject *> m_set_rabish;
		QMutex m_mutex_rabish_can;
		//Extra Data
		QHash<QObject *, quint64> m_extraData;
		void push_to_rabish_can(QObject * deletedobj);
	public slots:
		//This slot dealing with multi-thread client socket accept.
		void incomingConnection(QObject * threadid,qintptr socketDescriptor);
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

	protected slots:
		//when client closed, this slot will be activated.
		void client_closed();
		void new_data_recieved();
		void some_data_sended(qint64);
		void displayError(QAbstractSocket::SocketError socketError);
		//Plain Connected
		void on_connected();
		//SSL Encrypted started
		void on_encrypted();
	signals:
		void evt_Message(QObject * psource,QString );
		void evt_SocketError(QObject * senderSock ,QAbstractSocket::SocketError socketError, quint64 extraData);
		void evt_NewClientConnected(QObject * client, quint64 extraData);
		void evt_ClientEncrypted(QObject * client, quint64 extraData);
		void evt_ClientDisconnected(QObject * client, quint64 extraData);
		void evt_Data_recieved(QObject * ,QByteArray   , quint64 extraData);
		void evt_Data_transferred(QObject * client,qint64, quint64 extraData);
	};
}
#endif // ZP_NETTRANSTHREAD_H
