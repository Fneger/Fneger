#ifndef CCOMMON_H
#define CCOMMON_H

#include <QSettings>
#include "st_message.h"

using namespace BdUgdServer;

extern QSettings Settings;

class QListWidget;
class CTcpClient;
class CCommon
{
public:
    CCommon();
    static CCommon *Instance();
    void SetTcpClient(CTcpClient *pTcpClient) { m_tcpClient = pTcpClient; }
    void RemoveItem(QListWidget *listWidget,int row);
    void RemoveAllItems(QListWidget *listWidget);
    QStringList GetProductList();
    bool GetProductInfo(const QString &name, PRODUCT_INFO_S &info);
    QMap<QString, PRODUCT_INFO_S> LoadProducts();
    void getCpuId(unsigned int CPUInfo[4], unsigned int InfoType);
    void getCpuIdex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);
    QString getCpuId();
    QString getCpuId(const QString id);
    void PutVersionInfo(const VERSION_INFO_S &info, QJsonObject &infoObj);
    void GetVersionInfo(VERSION_INFO_S &info, const QJsonObject &infoObj);
    QString GetEventName(int type);
    QString GetEventDeviceIdTypeName(int type);
    QString GetEventStatusName(int status);
    QMap<quint64,EVENT_INFO_S> QueryEvents();
    bool AddLog2Db(CTcpClient *pClient, const QString &productName, const QString &devNum, const QString &imeiNumber, const QString &fwVer, int type, int subtype, int result, const QString &msg);
private:
    CTcpClient *m_tcpClient;
};

#endif // CCOMMON_H
