#include "boost/thread.hpp"
#include "ctestthread.h"
#include "casiotcpclient.h"
#include <QDebug>


CTestThread::CTestThread(QObject *parent) : QThread(parent)
{

}

void CTestThread::run()
{
    int client_total = 200;
    QList<boost::shared_ptr<CAsioTcpClient>> clients;
    QList<boost::shared_ptr<CAsioTcpClient>> rabissh_clients;
    boost::shared_ptr<CAsioTcpClient> pClient;
    char tMsg[] = "memory leak test";
    QList<boost::shared_ptr<CAsioTcpClient>>::iterator it;
    uint64_t cnt = 0;
    QThread eventTh;
    eventTh.start();
    for (;;)
    {
        cnt++;
        pClient = boost::make_shared<CAsioTcpClient>(16384);
        pClient->moveToThread(&eventTh);
        pClient->start("127.0.0.1", 25600);
        clients << pClient;

        boost::this_thread::sleep(boost::posix_time::microseconds(100));

#if 1
        if(clients.size() >= client_total)
        {
            int sendCnt = 0;
            for(it = clients.begin(); it != clients.end(); ++it) {
                sendCnt++;
                pClient = (*it);
                if(pClient->state() == 4)
                {
                    if(sendCnt % 5 == 0)
                    {
                        pClient->queryDefaultVersion();
                        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
                    }
                    else
                    {
                        pClient->sendHeartbeat();
                        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
                    }

                }
            }
        }

#endif
        if(clients.size() > client_total)
        {
            boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
            while(clients.size() > client_total - 100)
            {
                pClient = clients.first();
                pClient->stop();
                rabissh_clients.push_back(pClient);
                clients.removeFirst();
                boost::this_thread::sleep(boost::posix_time::milliseconds(50));
            }

            boost::this_thread::sleep(boost::posix_time::microseconds(200));
            qDebug() << "clients size:" << clients.size() << cnt;
            boost::this_thread::sleep(boost::posix_time::microseconds(200));
        }


        while(rabissh_clients.size() > 16){
            rabissh_clients.removeFirst();
        }
    }

    clients.clear();
    eventTh.quit();
    eventTh.wait();
}
