#ifndef CSOCKETSESSION_H
#define CSOCKETSESSION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/system_error.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>
#include <string>

using boost::asio::ip::tcp;
class CAsioListen;
class CSocketSession;
typedef boost::shared_ptr<CSocketSession> session_ptr;
class CSocketSession :
        public boost::enable_shared_from_this<CSocketSession>,
        private boost::asio::noncopyable
{
public:

    typedef boost::function<void()> EventCallback;
    typedef boost::function<void(int, const std::string &)> ErrorEventCallback;
    typedef boost::function<bool(const char *, size_t)> ReadEventCallback;
    typedef boost::function<bool(size_t, size_t)> WriteEventCallback;
    typedef boost::function<void()> CloseEventCallback;
    typedef boost::function<void(int, const std::string &, uint16_t)> HostConnectedEventCallback;

    CSocketSession(boost::asio::io_service &service, size_t size);
    virtual ~CSocketSession() {
        if (socket().is_open()) {
            socket().close();
        }
        //qDebug() << __FUNCTION__;
    }

    void setHostConnectedCallback(HostConnectedEventCallback cb)
    { hostConnectedCallback_ = std::move(cb); }
    void setFinedHostedCallback(EventCallback cb)
    { finedHostedCallback_ = std::move(cb); }
    void setReadCallback(ReadEventCallback cb)
    { readCallback_ = std::move(cb); }
    void setWriteCallback(WriteEventCallback cb)
    { writeCallback_ = std::move(cb); }
    void setCloseCallback(CloseEventCallback cb)
    { closeCallback_ = std::move(cb); }
    void setErrorCallback(ErrorEventCallback cb)
    { errorCallback_ = std::move(cb); }

    inline void connectToHost(const std::string & hostName, int16_t port) {
        if (resolver_ == nullptr)
            resolver_.reset(new boost::asio::ip::tcp::resolver(stand_.context()));
        resolver_->async_resolve(boost::asio::ip::tcp::resolver::query(hostName,std::to_string(port)),
                                 stand_.wrap(boost::bind(&CSocketSession::resolverHandle,
                                                        shared_from_this(), boost::asio::placeholders::error,boost::asio::placeholders::iterator)));
#if 0
        try {

        } catch (boost::exception &e) {
            qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
        }
#endif
    }

    inline  void wirteData(const char * data, int size) {
        if (is_open()) {
            memcpy(tx_buffer_.data(), data, size);
                boost::asio::async_write(socket(),boost::asio::buffer(tx_buffer_.data(),size),
                                  stand_.wrap(boost::bind(&CSocketSession::writeHandler,shared_from_this(),
                                                         boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred, size)));
        }
#if 0
        try {

        } catch (boost::exception &e) {
            qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
        }
#endif
    }

    inline void disconnectFromHost() {
        if (resolver_ != nullptr) resolver_->cancel();
        if (socket().is_open()) {
            socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both,erro_code);
            //                socket().close();
        }
#if 0
        try {

        } catch (boost::exception &e) {
            qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
        }
#endif
    }


    inline void do_read() {
        socket().async_read_some(boost::asio::buffer(rx_buffer_,rx_buffer_.size()),
                                 stand_.wrap(boost::bind(&CSocketSession::readHandler,shared_from_this(),
                                                        boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred)));
#if 0
        try {

        } catch (boost::exception &e) {
            qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
        }
#endif
    }

    void do_connect(boost::asio::ip::tcp::resolver::iterator & iter) {
        boost::asio::async_connect(socket(),iter,
                            stand_.wrap(boost::bind(&CSocketSession::connectedHandler,
                                                   shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::iterator)));
#if 0
        try {

        } catch (boost::exception &e) {
            qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
        }
#endif
    }

    inline bool is_open() {
        return socket().is_open();
    }

    inline  int socketDescriptor() {
        return static_cast<int>(socket().native_handle());
    }

    inline boost::asio::ip::tcp::socket & socket(){
        return (socket_);
    }

protected:
    void readHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
    void writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred, std::size_t will_bytes_transferred);
    void connectedHandler(const boost::system::error_code& error,boost::asio::ip::tcp::resolver::iterator iter);
    void resolverHandle(const boost::system::error_code & error, boost::asio::ip::tcp::resolver::iterator iter);

protected:
    inline void setError(const boost::system::error_code & erro, std::string && erro_string){
        erro_code = erro;
        erro_string.append(erro_code.message().c_str());
        disconnectFromHost();
        if(errorCallback_)
            errorCallback_(erro.value(), erro_string);
    }

    template <typename SettableSocketOption>
    void  set_option(const SettableSocketOption& option){
        socket().set_option(option,erro_code);
    }

    template <typename SettableSocketOption>
    void get_option(SettableSocketOption & option) {
        socket().get_option(option,erro_code);
    }

protected :
    boost::system::error_code erro_code;
    boost::scoped_ptr<boost::asio::ip::tcp::resolver> resolver_;
    std::vector<char> tx_buffer_;
    std::vector<char> rx_buffer_;
    boost::asio::io_service::strand stand_;
    boost::asio::ip::tcp::socket socket_;
    EventCallback finedHostedCallback_;
    HostConnectedEventCallback hostConnectedCallback_;
    ReadEventCallback readCallback_;
    WriteEventCallback writeCallback_;
    CloseEventCallback closeCallback_;
    ErrorEventCallback errorCallback_;
};

#endif // CSOCKETSESSION_H
