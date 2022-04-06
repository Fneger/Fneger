#ifndef QBOOSTASIOTCPSERVER_H
#define QBOOSTASIOTCPSERVER_H

#include <QObject>
#include "qsocketsession.h"

using namespace boost::asio;



class QBoostAsioTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit QBoostAsioTcpServer(quint16 nPort, QObject *parent = nullptr);
    ~QBoostAsioTcpServer();
    bool listen();
    boost::asio::io_service& get_io_service() { return m_io_srv; }

signals:

public slots:



private:
    io_service m_io_srv;
    io_service::work m_work;
    ip::tcp::acceptor m_acceptor;

    void handle_accept(socket_session_ptr session, const boost::system::error_code& error);
    void close_callback(socket_session_ptr session);
    void read_data_callback(const boost::system::error_code& e,
        socket_session_ptr session, QByteArray & msg);
};

#endif // QBOOSTASIOTCPSERVER_H
