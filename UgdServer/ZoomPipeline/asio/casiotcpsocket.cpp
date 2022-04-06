#include "ioserviceclass.h"
#include "casiotcpsocket.h"
#include <QMutex>
#include <QDateTime>

static QMutex mut;

boost::shared_ptr<IOServiceClass> CAsioTcpSocket::s_ioserver_;
volatile ulong CAsioTcpSocket::s_linkCout_ = 0;

CAsioTcpSocket::CAsioTcpSocket(size_t size,QObject *parent) :
    CTcpAbstractSocket(parent),serverBuild_(false), isNewClient_(true)
{
    mut.lock();
    if (s_ioserver_ == nullptr) {
        s_ioserver_.reset(new IOServiceClass(boost::thread::hardware_concurrency()));
    }
    ++ s_linkCout_;
    mut.unlock();
    clientSsession_.reset(new CSocketSession(s_ioserver_->getService(),size));
}

CAsioTcpSocket::CAsioTcpSocket(session_ptr ses) :
    CTcpAbstractSocket(nullptr), serverBuild_(true), con_(ses), isNewClient_(true)
{

}

CAsioTcpSocket::~CAsioTcpSocket()
{
    if (!serverBuild_) {
        mut.lock();
        -- s_linkCout_;
        if (s_linkCout_ == 0) {
            s_ioserver_.reset((IOServiceClass*)nullptr);
        }
        mut.unlock();
    }
//    qDebug() << __FUNCTION__;
}

void CAsioTcpSocket::init()
{
    if(serverBuild_)
        session_ = con_;
    else
        session_ = clientSsession_;
    isNewClient_ = true;
    activeTime_ = QDateTime::currentSecsSinceEpoch();
    int soc = session_->socketDescriptor();
    if (soc != -1) {
        setState(ConnectedState);
        setSocketPtr(soc);
    }

    try {
        session_->setReadCallback(boost::bind(&CAsioTcpSocket::readDataed, this, _1, _2));
        session_->setWriteCallback(boost::bind(&CAsioTcpSocket::writeDataed, this, _1, _2));
        session_->setHostConnectedCallback(boost::bind(&CAsioTcpSocket::hostConnected, this, _1, _2, _3));
        session_->setFinedHostedCallback(boost::bind(&CAsioTcpSocket::finedHosted, this));
        session_->setErrorCallback(boost::bind(&CAsioTcpSocket::haveErro, this, _1, _2));
    } catch (boost::exception &e) {
         qDebug() << __FUNCTION__ << __LINE__ << boost::diagnostic_information(e).c_str();
    }
}

void CAsioTcpSocket::setSession(session_ptr ses)
{
    con_ = ses;
}

void CAsioTcpSocket::do_start()
{
    session_->do_read();
}

void CAsioTcpSocket::hostConnected1()
{
    setState(ConnectedState);
    Q_EMIT connected();
    Q_EMIT stateChange(state());
    session_->do_read();
}

void CAsioTcpSocket::connectToHost(const QString &hostName, quint16 port)
{
    if (state() != UnconnectedState)
        session_->disconnectFromHost();
    setState(HostFinding);
    session_->connectToHost(hostName.toStdString(),port);
}

void CAsioTcpSocket::disconnectFromHost()
{
    if (state() == UnconnectedState) return;
    Q_EMIT disConnected();
    session_->disconnectFromHost();
}

void CAsioTcpSocket::sendData(const char * data, int size)
{
    if (state() == ConnectedState)
    {
        session_->wirteData(data,size);
    }
}

int CAsioTcpSocket::resizeClientBackThreadSize(int size)
{
    if (serverBuild_) return -1;
    return s_ioserver_->setThreadSize(size);
}

void CAsioTcpSocket::updateActiveTime()
{
    activeTime_ = QDateTime::currentSecsSinceEpoch();
}
