#ifndef QSOCKETSESSION_H
#define QSOCKETSESSION_H

#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <QByteArray>

using boost::asio::ip::tcp;

class QSocketSession;
typedef boost::shared_ptr<QSocketSession> socket_session_ptr;

class QSocketSession : public boost::enable_shared_from_this<QSocketSession>, private boost::asio::noncopyable
{
public:
    typedef boost::function<void(socket_session_ptr)> close_callback;
            typedef boost::function<void(
                const boost::system::error_code&,
                socket_session_ptr, QByteArray &)> read_data_callback;

    QSocketSession(boost::asio::io_service &io_service);
    virtual ~QSocketSession();
    tcp::socket& socket() { return m_socket; }

    void installCloseCallBack(close_callback cb){ close_cb = cb; }
    void installReadDataCallBack(read_data_callback cb) { read_data_cb = cb; }

    void start();
    void close();

    void async_write(const std::string& sMsg);
    void async_write(QByteArray& msg);

private:
    boost::asio::io_service &m_io_service;
    tcp::socket m_socket;
    close_callback close_cb;
    read_data_callback read_data_cb;

    //发送消息
    void handle_write(const boost::system::error_code& e,
        std::size_t bytes_transferred, std::string* pmsg);

    //读消息头
    void handle_read_header(const boost::system::error_code& error);
    //读消息体
    void handle_read_body(const boost::system::error_code& error);

    void handle_close();
};

#endif // QSOCKETSESSION_H
