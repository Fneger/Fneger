#ifndef CTCPCLIENTTEST_H
#define CTCPCLIENTTEST_H

#include "mythread.h"
#include <QMap>

class CTcpClient;
class QTimer;
class CTcpClientTest : public CMyThread
{
    Q_OBJECT
public:
    explicit CTcpClientTest(quint64 nStartUUID, quint64 nEndUUID, QObject *parent = nullptr);
    ~CTcpClientTest();
    void startStopTest(bool bIsStart);

signals:

private slots:
private:
    void run();

private:
    QList<CTcpClient *> m_clients;
    quint64 m_maxUUID;
    quint64 m_minUUID;
    quint64 m_currNewUUID;
    QMutex m_clientsMutex;
};

#endif // CTCPCLIENTTEST_H
