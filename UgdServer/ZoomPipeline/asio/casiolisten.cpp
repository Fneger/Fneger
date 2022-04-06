#include "casiolisten.h"
#include "casiotcpserver.h"
#include <QDebug>

CAsioListen::CAsioListen(const boost::weak_ptr<CAsioTcpServer> &wkServer, boost::asio::io_service &io_s, size_t socket_buffer)
    : m_io_svr(io_s), m_acceptor(io_s, tcp::endpoint(tcp::v4(), 25600))
    , m_strand(io_s)
    , m_buffer_size(socket_buffer), m_tcp_server(wkServer)
{

}

CAsioListen::~CAsioListen()
{

}

bool CAsioListen::listen(boost::asio::ip::tcp::endpoint &endpot)
{
    close();
    m_acceptor.open(endpot.protocol());
    m_acceptor.bind(endpot,m_erro_code);
    if (m_erro_code)
        return false;
    m_acceptor.listen(boost::asio::socket_base::max_connections, m_erro_code);
    if (m_erro_code){
        close();
        return false;
    }
    do_appent();
    return true;
}

void CAsioListen::close()
{
    if (m_acceptor.is_open()){
        m_acceptor.close();
    }
}

void CAsioListen::handle_accept(const boost::system::error_code &error)
{
    if(!error)
    {
        if(m_new_session)
        {
            boost::shared_ptr<CAsioTcpServer> pServer(m_tcp_server.lock());
            pServer->incomingConnection(m_new_session);
        }
        do_appent();
    }
}
