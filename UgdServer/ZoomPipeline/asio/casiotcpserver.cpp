#include "boost/asio.hpp"
#include "casiolisten.h"
#include "casiotcpserver.h"
#include <QDebug>

CAsioTcpServer::CAsioTcpServer(size_t socket_buffer, QObject *parent)
    : QObject(parent), m_buffer_size(socket_buffer)
{
    m_io_svr.setThreadSize(boost::thread::hardware_concurrency());
}
CAsioTcpServer::~CAsioTcpServer()
{
}

void CAsioTcpServer::init()
{
    try {
        m_listen.reset(new CAsioListen(boost::weak_ptr<CAsioTcpServer>(shared_from_this()), m_io_svr.getService(), m_buffer_size));
    } catch (boost::exception &e) {
        qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
    }
}

void CAsioTcpServer::incomingConnection(session_ptr session)
{
#if 0
    CAsioTcpSocket * socket = new CAsioTcpSocket(session);
    socket->Init();
    socket->moveToThread(this->thread());
    connect(this,&CAsioTcpServer::deleteAllLink,socket,&CAsioTcpSocket::deleteLater);
    Q_EMIT newConnection(socket);
#else
    Q_EMIT evt_NewClientArrived(session);
#endif
    //qDebug() << "incomingConnection";
}

void CAsioTcpServer::setSocketOption(CTcpAbstractSocket::SocketOption option, bool isEnble, uint value)
{
    //listen_session->setSocketOption(option,isEnble,value);
}

bool CAsioTcpServer::listen(const QString & ip,qint16 port)
{
    close();
    boost::system::error_code code;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(ip.toStdString(),code);
    boost::asio::ip::tcp::endpoint endpot(address,port);

    return m_listen->listen(endpot);
}

void CAsioTcpServer::close()
{
    m_listen->close();
}

int CAsioTcpServer::setThreadSize(size_t  size)
{
    return m_io_svr.setThreadSize(size);
}


