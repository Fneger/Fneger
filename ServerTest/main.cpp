#include <QCoreApplication>
#include "boost/asio.hpp"
#include "boost/thread.hpp"
#include <iostream>
#include <QDebug>
#include "zp_tcpserver.h"
#include "ctestthread.h"

void handler1(const boost::system::error_code &ec)
{
  std::cout << "5 s." << std::endl;
}

void handler2(const boost::system::error_code &ec)
{
  std::cout << "5 s." << std::endl;
}

boost::asio::io_service io_service;

void run()
{
  io_service.run();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(5));
    timer1.async_wait(handler1);
    boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(5));
    timer2.async_wait(handler2);
    boost::thread thread1(run);
    boost::thread thread2(run);
    //thread1.join();
    //thread2.join();
    qDebug() << "waitting...";

    //ZPNetwork::ZP_TcpServer tcpServer;
    //tcpServer.listen("0.0.0.0", 25600);
    CTestThread tTh[8];
    for(int i = 0; i < 8; i++){
        tTh[i].start();
    }
    return a.exec();
}
