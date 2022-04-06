#include "qsocketsession.h"
#include <QDebug>

QSocketSession::QSocketSession(boost::asio::io_service &io_service)
    : m_io_service(io_service), m_socket(io_service)
{

}

QSocketSession::~QSocketSession()
{
    m_socket.close();
}

void QSocketSession::start()
{
    m_socket.set_option(boost::asio::ip::tcp::acceptor::linger(true, 0));
    m_socket.set_option(boost::asio::socket_base::keep_alive(true));
    const boost::system::error_code error;
    handle_read_header(error);
}

void QSocketSession::handle_close()
{
    try{
        m_socket.close();
        close_cb(shared_from_this());
    }
    catch(std::exception& e)
    {
        qDebug() << "����Զ�̵�ַ:[" << this << "],socket�쳣:[" << e.what() << "]";
    }
    catch(...)
    {
        qDebug() << "����Զ�̵�ַ:[" << this << "],socket�쳣:[δ֪�쳣]";
    }
}

void QSocketSession::close()
{
    //���ڻص����м���������������ύ������һ���߳�ȥ������Ȼ���������
    m_io_service.post(boost::bind(&QSocketSession::handle_close, shared_from_this()));
}
