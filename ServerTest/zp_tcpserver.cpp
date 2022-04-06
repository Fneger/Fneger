#include "zp_tcpserver.h"
#include "casiotcpsocket.h"

namespace ZPNetwork{
	ZP_TcpServer::ZP_TcpServer(QObject *parent )
        : CAsioTcpServer(10240,parent)
	{

	}

    void ZP_TcpServer::incomingConnection(session_ptr session)
    {
        CAsioTcpSocket *pSock = new CAsioTcpSocket(session);
        pSock->init();
        pSock->do_start();
       // Q_EMIT evt_NewClientArrived(session);
    }
}
