#include "qboostasiotcpserver.h"
#include <QDebug>

QBoostAsioTcpServer::QBoostAsioTcpServer(quint16 nPort, QObject *parent)
    : QObject(parent), m_work(m_io_srv), m_acceptor(m_io_srv, ip::tcp::endpoint(ip::tcp::v4(), nPort))
{

}

QBoostAsioTcpServer::~QBoostAsioTcpServer()
{

}

bool QBoostAsioTcpServer::listen()
{
    bool res = true;
    try {
        socket_session_ptr new_session(new QSocketSession(m_io_srv));
        m_acceptor.async_accept(new_session->socket(), boost::bind(&QBoostAsioTcpServer::handle_accept, this, new_session,
                                                                  boost::asio::placeholders::error));
    } catch (std::exception& e) {
        res = false;
        qDebug() << "socket abnormal:[" << e.what() << "]";
    } catch(...)
    {
        res = false;
        qDebug() << "socket abnormal:[unknow]";
    }
    return res;
}

void QBoostAsioTcpServer::handle_accept(socket_session_ptr session, const boost::system::error_code &ec)
{
    if(!ec)
    {
        try {
            socket_session_ptr new_session(new QSocketSession(m_io_srv));
            m_acceptor.async_accept(new_session->socket(), boost::bind(&QBoostAsioTcpServer::handle_accept, this, new_session,
                                                                      boost::asio::placeholders::error));
            if(session != nullptr)
            {
                //注册关闭回调函数
                session->installCloseCallBack(boost::bind(&QBoostAsioTcpServer::close_callback, this, _1));
                //注册读到数据回调函数
                session->installReadDataCallBack(boost::bind(&QBoostAsioTcpServer::read_data_callback, this, _1, _2, _3));
            }
        } catch () {

        }
    }
    qDebug() << "new client connected...";
}

void QBoostAsioTcpServer::close_callback(socket_session_ptr session)
    {
        qDebug() << "close_callback";
        try{
           // m_manager.del_session<sid>(session->id());
        }
        catch (std::exception& e) {
                qDebug() << "socket abnormal:[" << e.what() << "]";
        } catch(...)
        {
            qDebug() << "socket abnormal:[unknow]";
        }

    }
