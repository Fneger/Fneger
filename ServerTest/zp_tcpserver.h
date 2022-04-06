#ifndef ZP_TcpServer_H
#define ZP_TcpServer_H

//#include <QTcpServer>
#include "casiotcpserver.h"

namespace ZPNetwork{
    class ZP_TcpServer : public CAsioTcpServer
	{
		Q_OBJECT

	public:
        ZP_TcpServer(QObject *parent = nullptr);
	protected:
        void incomingConnection(session_ptr session);
	signals:
        void evt_NewClientArrived(session_ptr session);
	};
}
#endif // ZP_TcpServer_H
