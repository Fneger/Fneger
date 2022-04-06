#include "zpmainframe.h"
#include "ui_zpmainframe.h"
#include "ssl_config.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QMap>
#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>
#include <QHostInfo>
#include <QDebug>
#if (ZP_WANTSSL!=0)
#include <QSslSocket>
#endif
#include "zp_tcpserver.h"
#include "zp_clusterterm.h"
#include "databasetool.h"
#include "st_client_file.h"
#include "cgarbagecollector.h"
#include <QDir>
#include "casiotcpsocket.h"
#include "casiodatabase.h"

using namespace ZPNetwork;
using namespace ZPTaskEngine;
using namespace ZP_Cluster;
using namespace ZPDatabase;

extern quint64 g_bytesRecieved;
extern quint64 g_bytesSent;
extern quint64 g_secRecieved;
extern quint64 g_secSent;

ZPMainFrame::ZPMainFrame(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::ZPMainFrame)
    ,m_pLogger(nullptr)
{
    QDir dir;
    dir.mkdir("./version");
    dir.mkdir("./device_file");

    m_currentConfigFile = "config.ini";
    ui->setupUi(this);

    //Create net engine
    m_netEngine = new zp_net_Engine (DATA_PAYLOAD);
    connect (m_netEngine,&zp_net_Engine::evt_SocketError,this,&ZPMainFrame::slot_evt_SocketError, Qt::QueuedConnection);
    //Create TaskEngine
    m_taskEngine = new zp_pipeline(this);

#if 0
    //Cluster is not created
    m_pClusterTerm = new ZP_Cluster::zp_ClusterTerm("Unknown",this);
    connect (m_pClusterTerm,&ZP_Cluster::zp_ClusterTerm::evt_Message,this,&ZPMainFrame::slot_evt_Message_Cluster);
    connect (m_pClusterTerm,&ZP_Cluster::zp_ClusterTerm::evt_SocketError,this,&ZPMainFrame::slot_evt_SocketError_Cluster);
#endif

    //Create databases
    m_pDatabases = new ZPDatabase::DatabaseResource(this);
    connect (m_pDatabases,&ZPDatabase::DatabaseResource::evt_Message,this,&ZPMainFrame::slot_evt_Message_Database, Qt::QueuedConnection);
    m_pDatabases->start();

    //Create Smartlink client table
    m_clientTable = new ExampleServer::st_client_table (m_netEngine,
                                                    m_taskEngine,
                                                    m_pDatabases,
                                                        nullptr,
                                                    this);
    connect (this, &ZPMainFrame::evt_KickDeadClients,m_clientTable,&ExampleServer::st_client_table::KickDeadClients, Qt::QueuedConnection);

    st_client_file::setClientTable(m_clientTable);
    CAsioDatabase::s_client_table_ = m_clientTable;

    CGarbageCollector::Instance()->startCollection();

    m_nTimerId = startTimer(2000);
    m_nTimerCheck =  startTimer(10000);
    //m_nPrintLog = startTimer(500);
    m_nPrintLog = -1;

    initUI();

    m_pTrayMenu = new QMenu (this);
    m_pTrayMenu->addAction(ui->actionShow_Window);
    m_pTrayMenu->addAction(ui->actionExit);

    m_IconTray = new QSystemTrayIcon(QIcon(":/icons/Resources/Color Classic.png"),this);
    m_IconTray->setContextMenu(m_pTrayMenu);
    m_IconTray->show();
}

ZPMainFrame::~ZPMainFrame()
{
    m_netEngine->RemoveAllAddresses();
    qApp->processEvents();
    m_netEngine->KickAllClients();
    qApp->processEvents();
    m_netEngine->DeactiveImmediately();
    qApp->processEvents();
    //term the confirm check
    m_pDatabases->TerminateMe();
    qApp->processEvents();
    m_pDatabases->remove_connections();
    qApp->processEvents();
    m_taskEngine->removeThreads(-1);
    qApp->processEvents();

#if 0
    m_pClusterTerm->netEng()->RemoveAllAddresses();
    m_pClusterTerm->netEng()->KickAllClients();
    m_pClusterTerm->netEng()->DeactiveImmediately();
    m_pClusterTerm->taskEng()->removeThreads(-1);
#endif
    int maxWait = 0;
    while (m_netEngine->CanExit()==false || m_taskEngine->canClose()==false
           || m_pDatabases->isRunning()==true /*|| m_pClusterTerm->canExit()==fals*/)
    {
        QCoreApplication::processEvents();
        QThread::currentThread()->msleep(200);
        maxWait ++;
        if (maxWait>=150)
        {
            if (QMessageBox::information(0,tr("Confire Exit"),
                                         tr("There are still some clients alive in the server. continue waiting?"),
                                         QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                maxWait = 0;
            else
                break;
        }
    }

    CGarbageCollector::Instance()->stopCollection();
    qApp->processEvents();

    m_netEngine->deleteLater();
    m_pDatabases->deleteLater();
    m_taskEngine->deleteLater();
   // m_pClusterTerm->deleteLater();
    delete ui;
}

void ZPMainFrame::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::WindowStateChange:
        if (this->isMinimized()==true)
        {
            this->hide();
            this->m_IconTray->showMessage(tr("Server still running"),
                                          tr("If you want to terminate server, just using exit Toolbar button."));
        }
        break;
    default:
        break;
    }
}

void ZPMainFrame::setLogger(STMsgLogger::st_logger * plogger)
{
    this->m_pLogger = plogger;
}

void ZPMainFrame::initUI()
{
    //Message Shown model
#if 0
    m_pMsgModelNetwork = new QStandardItemModel(this);
    ui->listView_msg->setModel(m_pMsgModelNetwork);
    m_pMsgModelCluster = new QStandardItemModel(this);
    ui->listView_msg_cluster->setModel(m_pMsgModelCluster);
    m_pMsgModelDatabase = new QStandardItemModel(this);
    ui->listView_msg_database->setModel(m_pMsgModelDatabase);
    m_pMsgModelSmartlink = new QStandardItemModel(this);
    ui->listView_msg_smartlink->setModel(m_pMsgModelSmartlink);
    //Network listeners setting model
    m_pListenerModel = new QStandardItemModel(0,4,this);
    m_pListenerModel->setHeaderData(0,Qt::Horizontal,tr("Name"));
    m_pListenerModel->setHeaderData(1,Qt::Horizontal,tr("Addr"));
    m_pListenerModel->setHeaderData(2,Qt::Horizontal,tr("Port"));
    m_pListenerModel->setHeaderData(3,Qt::Horizontal,tr("SSL"));
    ui->tableView_listen->setModel(m_pListenerModel);


    //database
    m_pDbResModel = new QStandardItemModel(0,8,this);
    m_pDbResModel->setHeaderData(0,Qt::Horizontal,tr("Name"));
    m_pDbResModel->setHeaderData(1,Qt::Horizontal,tr("Type"));
    m_pDbResModel->setHeaderData(2,Qt::Horizontal,tr("HostAddr"));
    m_pDbResModel->setHeaderData(3,Qt::Horizontal,tr("Port"));
    m_pDbResModel->setHeaderData(4,Qt::Horizontal,tr("Database"));
    m_pDbResModel->setHeaderData(5,Qt::Horizontal,tr("Username"));
    m_pDbResModel->setHeaderData(6,Qt::Horizontal,tr("Options"));
    m_pDbResModel->setHeaderData(7,Qt::Horizontal,tr("TestSQL"));
    ui->tableView_dbconn->setModel(m_pDbResModel);
    QStringList fdrivers = QSqlDatabase::drivers();
    QStandardItemModel * pCombo = new QStandardItemModel(this);
    foreach (QString str, fdrivers)
    {
        pCombo->appendRow(new QStandardItem(str));
    }
    ui->comboBox_db_type->setModel(pCombo);


    m_pModelCluster= new QStandardItemModel(0,6,this);
    m_pModelCluster->setHeaderData(0,Qt::Horizontal,tr("Name"));
    m_pModelCluster->setHeaderData(1,Qt::Horizontal,tr("LAN_Address"));
    m_pModelCluster->setHeaderData(2,Qt::Horizontal,tr("LAN_Port"));
    m_pModelCluster->setHeaderData(3,Qt::Horizontal,tr("Clients"));
    m_pModelCluster->setHeaderData(4,Qt::Horizontal,tr("Pub_Address"));
    m_pModelCluster->setHeaderData(5,Qt::Horizontal,tr("Pub_Port"));
    ui->tableView_activeTerms->setModel(m_pModelCluster);
#endif
    m_pStatusLabel = new QLabel(this);
    this->statusBar()->addWidget(m_pStatusLabel);
    ui->action_Start_Stop->setChecked(true);
}

void ZPMainFrame::printLog(const QString &sLog)
{return;
    QMutexLocker autoLock(&m_logMutex);
    if(ui->actionStop_Debug->isChecked())
        return;
    m_logMsg.append(sLog);
}

void ZPMainFrame::startStop()
{
    static bool s_isStart = false;
    s_isStart = !s_isStart;
    if (s_isStart==true)
    {
        forkServer(m_currentConfigFile);
        //Cluster Reconnection Dtm Protect
        //m_dtmLastClusterJoin = QDateTime::currentDateTime();
    }
    else
    {
        m_netEngine->RemoveAllAddresses();
        m_netEngine->RemoveClientTransThreads(-1,true);
        m_netEngine->RemoveClientTransThreads(-1,false);
        m_taskEngine->removeThreads(-1);
        m_pDatabases->remove_connections();
#if 0
        this->m_pClusterTerm->netEng()->RemoveListeningAddress("clusterTerm");
        this->m_pClusterTerm->netEng()->RemoveClientTransThreads(-1,false);
        this->m_pClusterTerm->taskEng()->removeThreads(-1);
#endif

        /*while (m_netEngine->CanExit()==false || m_taskEngine->canClose()==false || m_pClusterTerm->canExit()==false)
        {
            QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            QThread::currentThread()->msleep(200);
        }*/

    }


}

void ZPMainFrame::forkServer(QString  config_file)
{
    QSettings settings(config_file,QSettings::IniFormat);
    int nListeners = settings.value("settings/listeners",0).toInt();
    if (nListeners<0)
        nListeners = 0;
    if (nListeners>=1024)
        nListeners = 1024;
    //read listeners from ini
    m_netEngine->RemoveAllAddresses();
    while (m_netEngine->ListenerNames().size())
    {
        QThread::currentThread()->msleep(200);
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }
#if 0
    for (int i=0;i<nListeners;i++)
    {
        QString keyPrefix = QString ("listener%1/").arg(i);
        QString listen_name = settings.value(keyPrefix+"name",
                                             QString("Listener%1").arg(i)).toString();
        QString Address =   settings.value(keyPrefix+"address",
                                           QString("127.0.0.1")).toString();
        QHostAddress listen_address (Address) ;

        int nPort = settings.value(keyPrefix+"port",23456+i).toInt();
        bool bSSL = settings.value(keyPrefix+"ssl",i%2?true:false).toBool();
        if (listen_address.isNull()==true || nPort<1024 || nPort>=32768 )
            continue;

        m_netEngine->AddListeningAddress(listen_name,listen_address,nPort,bSSL);
    }
#endif
    bool bSSL = false;
    QString localHostName = QHostInfo::localHostName();
    QHostAddress listen_address (localHostName) ;
    int listenPort = settings.value("settings/nListenPort",25600).toInt();
    m_netEngine->AddListeningAddress("UGD Client",listen_address,listenPort,bSSL);
    //read thread config
    int nSSLThreads = settings.value("settings/nSSLThreads",0).toInt();
    int nPlainThreads = settings.value("settings/nPlainThreads",8).toInt();
    int nWorkingThreads = settings.value("settings/nWorkingThreads",8).toInt();

    int nDeltaSSL = m_netEngine->TransThreadNum(true) - nSSLThreads;
    if (nDeltaSSL>0)
        m_netEngine->RemoveClientTransThreads(nDeltaSSL,true);
    else if (nDeltaSSL<0)
        m_netEngine->AddClientTransThreads(-nDeltaSSL,false);

    int nDeltaPlain = m_netEngine->TransThreadNum(false) - nPlainThreads;
    if (nDeltaPlain>0)
        m_netEngine->RemoveClientTransThreads(nDeltaPlain,false);
    else if (nDeltaPlain<0)
        m_netEngine->AddClientTransThreads(-nDeltaPlain,false);

    int nDeltaWorking = m_taskEngine->threadsCount() - nWorkingThreads;
    if (nDeltaWorking>0)
        m_taskEngine->removeThreads(nDeltaWorking);
    else
        m_taskEngine->addThreads(-nDeltaWorking);

    //database connections
    m_pDatabases->remove_connections();
    int nDBConns = settings.value("settings/dbresources",1).toInt();
    if (nDBConns>=1024)
        nDBConns = 1024;
    for (int i=0;i<nDBConns;i++)
    {
        QString keyPrefix = QString ("dbres%1/").arg(i);
        QString db_name = settings.value(keyPrefix+"name","test").toString();
        QString db_type = settings.value(keyPrefix+"type","QMYSQL").toString();
        QString db_Address = settings.value(keyPrefix+"addr","139.159.193.74").toString();
        int nPort = settings.value(keyPrefix+"port",3306).toInt();
        QString db_Schema = settings.value(keyPrefix+"schema","mysql").toString();
        QString db_User = settings.value(keyPrefix+"user","root").toString();
        QString db_Pass = settings.value(keyPrefix+"pass","GEM456123star").toString();
        QString db_Extra =  settings.value(keyPrefix+"extra","").toString();
        QString db_testSQL =  settings.value(keyPrefix+"testSql","show databases;").toString();
        if (db_name.length()<1 )
            continue;
        if (db_type.length()<1)
            continue;
        m_pDatabases->addConnection(
                    db_name,
                    db_type,db_Address,nPort,db_Schema,db_User,db_Pass,db_Extra,db_testSQL
                    );



    }


    //Smartlink settings
    int nHeartbeatingThreadhold = settings.value("Smartlink/HeartbeatingThreadhold",180).toInt();
    if (nHeartbeatingThreadhold>=60 && nHeartbeatingThreadhold<=300)
        m_clientTable->setHeartBeatingThrd(nHeartbeatingThreadhold);

    QString strSLDB_useracc = settings.value("Smartlink/SLDB_useracc","EMPTY").toString();
    m_clientTable->setDatabase_UserAcct(strSLDB_useracc);
    {
        st_client_file fileTool;
        USER_INFO_S userInfo;
        userInfo.name = "admin";
        userInfo.password = "456123";
        userInfo.auth = BdUserAuthAdmin_E;
        fileTool.addAuthUser(userInfo);
    }
    st_client_file::syncJson2Database();


    QString strSLDB_mainEvent = settings.value("Smartlink/SLDB_mainEvt","EMPTY").toString();
    m_clientTable->setDatabase_Event(strSLDB_mainEvent);

    QString strSL_LargetFolder = settings.value("Smartlink/SL_LargetFolder","NUL").toString();
    m_clientTable->setLargeFileFolder(strSL_LargetFolder);
    int nmaxBalance = settings.value("Smartlink/nmaxBalance","10240").toInt();
    m_clientTable->setBalanceMax(nmaxBalance);
#if 0
    //clusters
    QString strClusterTermAddr = settings.value("Cluster/strClusterTermAddr","0.0.0.0").toString();
    QString strClusterTermPort = settings.value("Cluster/strClusterTermPort","25600").toString();
    QString strClusterPubName = settings.value("Cluster/strClusterPubName","Term 001").toString();
    QString strClusterLANAddr = settings.value("Cluster/strClusterLANAddr","127.0.0.1").toString();
    QString strClusterLANPort = settings.value("Cluster/strClusterLANPort","25600").toString();
    QString strClusterPubAddr = settings.value("Cluster/strClusterPubAddr","192.168.1.111").toString();
    QString strClusterPubPort = settings.value("Cluster/strClusterPubPort","25600").toString();

    int nClusterTransThreads = settings.value("Cluster/nClusterTransThreads","4").toInt();
    int nClusterWorkingThreads = settings.value("Cluster/nClusterWorkingThreads","4").toInt();

    this->m_pClusterTerm->netEng()->RemoveAllAddresses();
    this->m_pClusterTerm->netEng()->RemoveClientTransThreads(-1,false);
    this->m_pClusterTerm->taskEng()->removeThreads(-1);
    while (m_pClusterTerm->netEng()->ListenerNames().size())
    {
        QThread::currentThread()->msleep(200);
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }
//    this->m_pClusterTerm->netEng()->AddClientTransThreads(nClusterTransThreads,false);
//    this->m_pClusterTerm->taskEng()->addThreads(nClusterWorkingThreads);
//    this->m_pClusterTerm->setName(strClusterPubName);
//    this->m_pClusterTerm->setLANAddr(QHostAddress(strClusterLANAddr));
//    this->m_pClusterTerm->setLANPort(strClusterLANPort.toInt());
//    this->m_pClusterTerm->setPublishAddr(QHostAddress(strClusterPubAddr));
//    this->m_pClusterTerm->setPublishPort(strClusterPubPort.toInt());
//    this->m_pClusterTerm->StartListen(QHostAddress(strClusterTermAddr),strClusterTermPort.toInt());
#endif

    int nRabbishCanSize = settings.value("settings/rubbish_can_size","32").toInt();
    ZPNetwork::zp_netTransThread::RUBBISH_CAN_SIZE = nRabbishCanSize;

//    if (this->windowTitle().indexOf("(")==-1)
//        this->setWindowTitle(windowTitle() + "(" + strClusterPubName +")");
}

void  ZPMainFrame::slot_evt_MessageNetwork(QObject * psource,QString  strMsg)
{
    qDebug() << strMsg;
    return;
#if 0
    int nrows = m_pMsgModelNetwork->rowCount();
    m_pMsgModelNetwork->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelNetwork->removeRow(m_pMsgModelNetwork->rowCount()-1);
#endif
}

void  ZPMainFrame::slot_evt_Message_Database(QObject * psource,QString strMsg)
{
    qDebug() << strMsg;
    return;
#if 0
    int nrows = m_pMsgModelDatabase->rowCount();
    m_pMsgModelDatabase->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelDatabase->removeRow(m_pMsgModelDatabase->rowCount()-1);
#endif
}

void  ZPMainFrame::slot_evt_Message_Smartlink(QObject * psource,QString strMsg)
{
    qDebug() << strMsg;
    return;
#if 0
    int nrows = m_pMsgModelSmartlink->rowCount();
    m_pMsgModelSmartlink->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelSmartlink->removeRow(m_pMsgModelSmartlink->rowCount()-1);
#endif

}

//The socket error message
void  ZPMainFrame::slot_evt_SocketError(QObject * senderSock ,const QString &erro)
{
    qDebug() << erro;
    return;
#if 0
    int nrows = m_pMsgModelNetwork->rowCount();
    m_pMsgModelNetwork->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelNetwork->removeRow(m_pMsgModelNetwork->rowCount()-1);
#endif

}

void  ZPMainFrame::slot_evt_Message_Cluster(QObject * psource,QString  strMsg)
{
    qDebug() << strMsg;
    return;
#if 0
    int nrows = m_pMsgModelCluster->rowCount();
    m_pMsgModelCluster->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelCluster->removeRow(m_pMsgModelCluster->rowCount()-1);
#endif
}

//The socket error message
void  ZPMainFrame::slot_evt_SocketError_Cluster(QObject * senderSock ,const QString &erro)
{
    qDebug() << erro;
    return;
#if 0
    int nrows = m_pMsgModelCluster->rowCount();
    m_pMsgModelCluster->insertRow(0,new QStandardItem(msg));
    while (nrows-- > 4096)
        m_pMsgModelCluster->removeRow(m_pMsgModelCluster->rowCount()-1);
#endif

}

void  ZPMainFrame::timerEvent(QTimerEvent * e)
{
    static int lastRecieved = 0;
    static int lastSent = 0;
    if (e->timerId()==m_nTimerId)
    {
        killTimer(m_nTimerId);
        m_nTimerId = -1;
        //recording net status
        QString str_msg;
        QStringList lstListeners = m_netEngine->ListenerNames();
        str_msg += tr("Current Listen Threads: %1\n").arg(lstListeners.size());
        for (int i=0;i<lstListeners.size();i++)
            str_msg += tr("\tListen Threads %1: %2\n").arg(i+1).arg(lstListeners.at(i));
        int nClientThreads = m_netEngine->TransThreadNum();
        int nRabishCanClients = 0;
        int nNewClientSockets = 0;

        str_msg += tr("Current Trans Threads: %1\n").arg(nClientThreads);
        int nTotalCLientsNums = 0;
        for (int i=0;i<nClientThreads;i++)
        {
            str_msg += tr("\t%1:%2").arg(i+1).arg(m_netEngine->totalClients(i));
            if ((i+1)%5==0)
                str_msg += "\n";
            nTotalCLientsNums += m_netEngine->totalClients(i);
            nRabishCanClients += m_netEngine->RabishCanSockets(i);
            nNewClientSockets += m_netEngine->NewClientSockets(i);
        }

        //Set This message to Cluster Info.
        //m_pClusterTerm->setClientNums(nTotalCLientsNums);

        str_msg += "\n";
        str_msg += tr("Current Total Trans Sockets: %1\n\n").arg(nTotalCLientsNums);
        str_msg += tr("Current Total New Client Sockets: %1\n\n").arg(nNewClientSockets);
        str_msg += tr("Current Total RabishCan Sockets: %1\n\n").arg(nRabishCanClients);
        str_msg += tr("Current Dead Socks: %1\n\n").arg(CGarbageCollector::Instance()->sockTrashSize());
        //recording task status
        str_msg += tr("Current Active Nodes: %1\n\n").arg(m_clientTable->ActiveNodes());
        str_msg += tr("Current NoActive Nodes: %1\n\n").arg(CGarbageCollector::Instance()->nodeNoactiveSize());
        str_msg += tr("Current Dead Nodes: %1\n\n").arg(CGarbageCollector::Instance()->nodeTrashSize());
        str_msg += tr("Current Task Threads: %1\n\n").arg(m_taskEngine->threadsCount());
        str_msg += tr("Current Task Payload: %1\n\n").arg(m_taskEngine->payload());
        str_msg += tr("Current Task Idle Threads: %1\n\n").arg(m_taskEngine->idleThreads());

        QMap<QString,ZPDatabase::DatabaseResource::tagConnectionPara> map_conns
                = m_pDatabases->currentDatabaseConnections();
        str_msg += tr("Database Connections: %1\n\n").arg(map_conns.size());
        foreach (QString name,map_conns.keys() )
        {
            ZPDatabase::DatabaseResource::tagConnectionPara & para = map_conns[name];
            str_msg += tr("\t%1 status = %2").arg(name).arg(para.status);
            if (para.status==false)
                str_msg += ", Msg=" + para.lastError;
            str_msg += "\n";
        }
#if 0
        //Cluster----------------------------

        str_msg += tr("Cluster Paras:\n");
        str_msg += tr("\tTerminal %1 : %2\n\t\tLAN Address: %3:%4\n\t\t Publish: %5:%6\n\t\tbalance max clients=%7\n")
                .arg(m_pClusterTerm->name())
                .arg(!m_pClusterTerm->netEng()->ListenerNames().empty())
                .arg(m_pClusterTerm->LANAddr().toString())
                .arg(m_pClusterTerm->LANPort())
                .arg(m_pClusterTerm->PublishAddr().toString())
                .arg(m_pClusterTerm->PublishPort())
                .arg(m_clientTable->balanceMax())
                ;

        nClientThreads = m_pClusterTerm->netEng()->TransThreadNum();
        str_msg += "\t"+tr("Trans Threads: %1\n").arg(nClientThreads);
        for (int i=0;i<nClientThreads;i++)
        {
            str_msg += tr("\t%1:%2").arg(i+1).arg(m_pClusterTerm->netEng()->totalClients(i));
            if ((i+1)%5==0)
                str_msg += "\n";
        }
        str_msg += "\n";
        str_msg += tr("\tShift Threads: %1\n").arg(m_pClusterTerm->taskEng()->threadsCount());
        str_msg += tr("\tShift Payload: %1\n").arg(m_pClusterTerm->taskEng()->payload());
        str_msg += tr("\tShift Idle Threads: %1\n").arg(m_pClusterTerm->taskEng()->idleThreads());


        str_msg += tr("Smartlink Function Server Paras:\n");
        str_msg += tr("\tUser Account Database is : %1\n").arg(m_clientTable->Database_UserAcct());
        str_msg += tr("\tEvent Database is : %1\n").arg(m_clientTable->Database_Event());
        str_msg += tr("\tLocal folder for large file is : %1\n").arg(m_clientTable->largeFileFolder());
        str_msg += tr("\tHeart beating Threadhold is : %1\n").arg(m_clientTable->heartBeatingThrd());


        //The Cluster Info
        QStringList lstCluster = m_pClusterTerm->SvrNames();
        if (m_pModelCluster->rowCount()>0)
            m_pModelCluster->removeRows(0,m_pModelCluster->rowCount());
        int nInserted = 0;
        m_pModelCluster->insertRow(nInserted);
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,0),this->m_pClusterTerm->name());
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,1),m_pClusterTerm->LANAddr().toString());
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,2),m_pClusterTerm->LANPort());
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,3),m_pClusterTerm->clientNums());
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,4),m_pClusterTerm->PublishAddr().toString());
        m_pModelCluster->setData(m_pModelCluster->index(nInserted,5),m_pClusterTerm->PublishPort());

        ++nInserted;
        foreach (QString strNodeName,lstCluster)
        {
            m_pModelCluster->insertRow(nInserted);
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,0),strNodeName);
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,1),m_pClusterTerm->SvrLANAddr(strNodeName).toString());
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,2),m_pClusterTerm->SvrLANPort(strNodeName));
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,3),m_pClusterTerm->remoteClientNums(strNodeName));
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,4),m_pClusterTerm->SvrPubAddr(strNodeName).toString());
            m_pModelCluster->setData(m_pModelCluster->index(nInserted,5),m_pClusterTerm->SvrPubPort(strNodeName));
            ++nInserted;
        }
#endif
        ui->plainTextEdit_status_net->setPlainText(str_msg);
        QString str = QDateTime::currentDateTime().toString();
        str += tr(" Rec %1B(%3 kbps)  Sent %2B(%4 kbps)")
                .arg(g_bytesRecieved)
                .arg(g_bytesSent)
                .arg(g_secRecieved*8/1024/2)
                .arg(g_secSent*8/1024/2)
                ;
        if (g_bytesRecieved != lastRecieved || g_bytesSent != lastSent)
        {
            static int ppIc = 0;
            lastRecieved = g_bytesRecieved;
            lastSent = g_bytesSent;
            if (++ppIc % 2==0)
                m_IconTray->setIcon(QIcon(":/icons/Resources/Color Classic Green.png"));
            else
                m_IconTray->setIcon(QIcon(":/icons/Resources/Color Classic, Performa 250, 275.png"));
        }
        else
        {
            m_IconTray->setIcon(QIcon(":/icons/Resources/Color Classic.png"));
        }
        g_secRecieved = g_secSent = 0;
        m_pStatusLabel->setText(str);
        m_nTimerId = startTimer(2000);
    }
    else if (e->timerId()==m_nTimerCheck)
    {
        killTimer(m_nTimerCheck);
        m_nTimerCheck = -1;
        Q_EMIT evt_KickDeadClients();
        //m_pClusterTerm->SendHeartBeatings();
        //m_pClusterTerm->KickDeadClients();
        m_netEngine->KickRabishCanClient();

#if 0
        //if (ui->action_Start_Stop->isChecked()==true)
        {
            //Cluster re-connection Test
            QStringList lstCluster = m_pClusterTerm->SvrNames();
            if (lstCluster.size()==0 && m_dtmLastClusterJoin.secsTo(QDateTime::currentDateTime())>=120)
            {
                m_pClusterTerm->netEng()->KickAllClients();
                QSettings settings(this->m_currentConfigFile,QSettings::IniFormat);
                QString strAddr = settings.value("history/clusterAddr","192.168.1.118").toString();
                QString strPort = settings.value("history/clusterPort","25600").toString();
                m_pClusterTerm->JoinCluster(QHostAddress(strAddr),strPort.toInt());
                m_dtmLastClusterJoin = QDateTime::currentDateTime();
            }
        }
#endif
        m_nTimerCheck = startTimer(10000);
    }
    else if(e->timerId() == m_nPrintLog)
    {
        killTimer(m_nPrintLog);
        m_nPrintLog = -1;
        m_logMutex.lock();
        QString msg = m_logMsg;
        m_logMsg.clear();
        m_logMutex.unlock();
        if(msg.length() > 0)
        {
            ui->DebugTextEdit->append(msg);
            QTextCursor cursor = ui->DebugTextEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->DebugTextEdit->setTextCursor(cursor);
            m_logMsg.clear();
        }
        m_nPrintLog = startTimer(500);
    }
}


void ZPMainFrame::slot_actionShow_Window_triggered()
{
    this->showNormal();
}
void  ZPMainFrame::closeEvent(QCloseEvent * e)
{
    if (this->isVisible()==true)
    {
        this->hide();
        this->m_IconTray->showMessage(tr("Server still running"),
                                      tr("If you want to terminate server, just using exit Toolbar button."));
        e->ignore();
    }
    else
    {
        e->accept();
        this->m_IconTray->showMessage(tr("Server is  going to closed"),
                                      tr("Waiting for all unfinished progress..."));
    }
}

void ZPMainFrame::slot_actionExit_triggered()
{
    this->hide();
    this->m_IconTray->setContextMenu(0);
    this->close();
}
