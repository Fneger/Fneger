#include "ctcpclienttest.h"
#include "ccommon.h"
#include "st_message.h"
#include "qghtcpclient.h"
#include "ctcpclient.h"
#include <QMessageBox>
#include <QTimer>
#include "st_global_def.h"

using namespace GsGlobalDef;
CTcpClientTest::CTcpClientTest(quint64 nStartUUID, quint64 nEndUUID, QObject *parent) : CMyThread(parent)
{
    m_minUUID = nStartUUID;
    m_maxUUID = nEndUUID;
    m_currNewUUID = nStartUUID;
}

CTcpClientTest::~CTcpClientTest()
{
    startStopTest(false);
}

void CTcpClientTest::startStopTest(bool bIsStart)
{
    if (bIsStart==true)
    {
        this->startRun();
    }
    else
    {
        this->stopRun();
    }
}

void CTcpClientTest::run()
{
    int nTotalClients = 100;
    int waitCnt = 10;

    while (!getQuitFlag()) {

        foreach(CTcpClient * client, m_clients)
        {

            if(getQuitFlag())
                break;
            if (rand()%100<50)
            {
#if 1
                if(!client->isStartTest())
                    client->startTest();
                if(client->isStartTest())
                {
                    if(!client->sendTestPacket(rand()%2048))
                    {
                        client->stopTest();
                        qWarning() << QString("client %1 test error!").arg(client->uuid(),16,16,QChar('0'));
                    }
#if 1
                    if(CCommon::Instance()->AddLog2Db(client,"ZH510", QString::number(rand() % 1024), "000000", "DVR-T21110194-ZH510.6550-ENG-BD.crc",
                                                      LOG_DEV_MODULE_E, DEV_MODULE_4G_E, DEV_MODULE_ABNORMAL_E,
                                                      "Dialing failed!"))
                    {
                        client->stopTest();
                        qWarning() << QString("client %1 test add log!").arg(client->uuid(),16,16,QChar('0'));
                    }
#endif

                }
#endif
            }

        }
        //
        //if (rand()%500 <100)
            //if (m_clients.size() < 1)
        {
            //1/10 chance to make new connections.
            if (m_clients.size()>nTotalClients)
            {
                while(m_clients.size() > nTotalClients){
                    m_clients.first()->stopClient();
                    m_clients.first()->deleteLater();
                    m_clients.removeFirst();
                    if(getQuitFlag())
                        break;
                }
            }
            QString serverIp = Settings.value("ServerSettings/sServerIp","127.0.0.1").toString();
            uint16_t serverPort = Settings.value("ServerSettings/nServerPort","25600").toString().toUInt();
            CTcpClient * client = new CTcpClient();
            m_currNewUUID++;
            if(m_currNewUUID > m_maxUUID)
                m_currNewUUID = m_minUUID;
            qDebug() << "New Client Id" << QString("%1").arg(m_currNewUUID, 8, 16, QChar('0')) << m_clients.size();
            client->setUuid(m_currNewUUID);
            client->setServerInfo(serverIp,serverPort);
            m_clients.push_back(client);
            client->startClient();
        }
        msleep(1000);
    }
    foreach(CTcpClient * client,m_clients)
    {
        client->stopClient();
        client->deleteLater();
    }
    m_clients.clear();
}
