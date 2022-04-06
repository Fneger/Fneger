#ifndef ZPMAINFRAME_H
#define ZPMAINFRAME_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QLabel>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QScopedPointer>
#include "st_logger.h"
#include "zp_net_threadpool.h"
#include "zp_pipeline.h"
#include "st_client_table.h"
#include "zp_clusterterm.h"


namespace Ui {
    class ZPMainFrame;
}
class QThread;
class ZPMainFrame : public QMainWindow
{
    Q_OBJECT
public:
    explicit ZPMainFrame(QWidget *parent = nullptr);
    ~ZPMainFrame();
    void timerEvent(QTimerEvent *);
    //Auto start support
    void LoadSettingsAndForkServer(const QString & configfile);
    void setLogger(STMsgLogger::st_logger * plogger);
    void startStop();
    void printLog(const QString &sLog);

Q_SIGNALS:
    void evt_KickDeadClients();

public Q_SLOTS:
    void slot_evt_MessageNetwork(QObject * psource,QString );
    //The socket error message
    void slot_evt_SocketError(QObject * senderSock , const QString &erro);
    void slot_evt_Message_Cluster(QObject * psource,QString );
    void slot_evt_Message_Database(QObject * psource,QString );
    void slot_evt_Message_Smartlink(QObject * psource,QString );
    //The socket error message
    void slot_evt_SocketError_Cluster(QObject * senderSock , const QString &erro);

    void slot_actionShow_Window_triggered();
    void slot_actionExit_triggered();

private:
    void forkServer(QString  config_file);
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent * e);
    void initUI();

private:
    Ui::ZPMainFrame *ui;
    QSystemTrayIcon * m_IconTray ;
    QMenu * m_pTrayMenu;
    QLabel * m_pStatusLabel;

    //QStandardItemModel * m_pMsgModelNetwork;
    //QStandardItemModel * m_pMsgModelCluster;
    //QStandardItemModel * m_pMsgModelDatabase;
    //QStandardItemModel * m_pMsgModelSmartlink;
    //Listeners settings
    //QStandardItemModel * m_pListenerModel;
    QSet<QString> m_set_listenerNames;
    //Database settings
    //QStandardItemModel * m_pDbResModel;
    QMap<QString,QString> m_set_DbResNames;

    //QStandardItemModel * m_pModelCluster;



    int m_nTimerId;
    //Dead check
    int m_nTimerCheck;
    int m_nPrintLog;
    //QDateTime m_dtmLastClusterJoin;
    //Config File Name
    QString m_currentConfigFile;
    STMsgLogger::st_logger * m_pLogger;
    ZPNetwork::zp_net_Engine * m_netEngine;
    ZPTaskEngine::zp_pipeline * m_taskEngine;
    ExampleServer::st_client_table * m_clientTable;
    ZPDatabase::DatabaseResource * m_pDatabases;
    //ZP_Cluster::zp_ClusterTerm * m_pClusterTerm;
    QMutex m_logMutex;
    QString m_logMsg;
};

#endif // ZPMAINFRAME_H
