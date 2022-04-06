#include "csocketsession.h"

CSocketSession::CSocketSession(boost::asio::io_service & service,size_t size)
    : resolver_(nullptr), stand_(service), socket_(service)
{
    rx_buffer_.resize(size);
    tx_buffer_.resize(size);
}

void CSocketSession::readHandler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if(!error){
        if ((readCallback_ != nullptr) && (readCallback_(rx_buffer_.data(),bytes_transferred))) {
            do_read();
        } else {
            disconnectFromHost();
        }
    } else {
        setError(error,"Read data erro: ");
    }
}


void CSocketSession::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred, std::size_t will_bytes_transferred)
{
    if (!error && bytes_transferred > 0){
        if ((writeCallback_ != nullptr) && (!writeCallback_(bytes_transferred,will_bytes_transferred)))
            disconnectFromHost();
    } else {
        setError(error,"Write data erro: ");
    }
}

void CSocketSession::resolverHandle(const boost::system::error_code &error, boost::asio::ip::tcp::resolver::iterator iter)
{
    if (!error && (finedHostedCallback_ != nullptr)) {
        finedHostedCallback_();
        do_connect(iter);
    } else {
        setError(error,"Rresolver domain erro: ");
    }
}


void CSocketSession::connectedHandler(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iter)
{
    if (!error) {
        boost::asio::ip::tcp::endpoint peerPoint;
#ifdef QASIO_SSL
        if (useSSL)
            peerPoint = sslSocketLty().remote_endpoint(erro_code);
        else
#endif
            peerPoint = socket().remote_endpoint(erro_code);

        if (hostConnectedCallback_ != nullptr) {
            hostConnectedCallback_(socketDescriptor(),peerPoint.address().to_string(),peerPoint.port());
        }
    } else {
        boost::asio::ip::tcp::resolver::iterator end;
        if(iter == end) {
            setError(error, "connect to host erro :");
        }
    }
}
