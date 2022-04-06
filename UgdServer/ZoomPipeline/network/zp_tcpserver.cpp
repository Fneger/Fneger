#include "zp_tcpserver.h"
#include <assert.h>
#include "st_message.h"

namespace ZPNetwork{
	ZP_TcpServer::ZP_TcpServer(QObject *parent )
        : CAsioTcpServer(DATA_PAYLOAD,parent)
	{

	}

    void ZP_TcpServer::incomingConnection(session_ptr session)
    {
        Q_EMIT evt_NewClientArrived(session);
    }
}
