#ifndef CASIOLISTEN_H
#define CASIOLISTEN_H

#include "boost/asio.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/weak_ptr.hpp"
#include <unordered_map>
#include "csocketsession.h"

using boost::asio::ip::tcp;
class CAsioTcpServer;
class CAsioListen;
class CAsioListen :
        public boost::enable_shared_from_this<CAsioListen>,
        public boost::asio::noncopyable
{
public:
    CAsioListen(const boost::weak_ptr<CAsioTcpServer> &wkServer, boost::asio::io_service &io_s, size_t socket_buffer = 4096);
    virtual ~CAsioListen();
    bool listen(boost::asio::ip::tcp::endpoint &endpot);
    void close();

private:
    boost::asio::io_service &m_io_svr;
    tcp::acceptor m_acceptor;
    boost::asio::io_service::strand m_strand;
    boost::system::error_code m_erro_code;
    size_t m_buffer_size;
    boost::weak_ptr<CAsioTcpServer> m_tcp_server;
    session_ptr m_new_session;

    void handle_accept(const boost::system::error_code &error);
    inline void do_appent(){
        m_new_session.reset(new CSocketSession(m_io_svr, m_buffer_size));

        m_acceptor.async_accept(m_new_session.get()->socket(),
                               m_strand.wrap(boost::bind(&CAsioListen::handle_accept,
                                                         this,
                                                         boost::asio::placeholders::error)));
    }
};

#endif // CASIOLISTEN_H
