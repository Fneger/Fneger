#include "ctcpabstractsocket.h"

CTcpAbstractSocket::CTcpAbstractSocket(QObject *parent) : QObject(parent)
{

}

void CTcpAbstractSocket::hostConnected1()
{
    setState(ConnectedState);
    Q_EMIT stateChange(state_);
    Q_EMIT connected();
}

void CTcpAbstractSocket::haveErro(int erro_code, const std::string &erro_string)
{
    this->erro_code = erro_code;
    this->erro_string = QString::fromStdString(erro_string);
    setState(UnconnectedState);
    handle = -1;
    peerPort_ = 0;
    peerIp_.clear();
    haveErro();
}
void CTcpAbstractSocket::hostConnected(int handle_id, const std::string &ip, uint16_t prot)
{
    handle = handle_id;
    peerIp_ = QString::fromStdString(ip);
    peerPort_ = prot;
    hostConnected1();
}

void CTcpAbstractSocket::haveErro()
{
        Q_EMIT erroString(QString("ec(%1), %2").arg(erro_code).arg(erro_string));
        Q_EMIT stateChange(state_);
        Q_EMIT disConnected();
}

bool CTcpAbstractSocket::readDataed(const char * data,std::size_t bytes_transferred)
{
        Q_EMIT sentReadData(QByteArray(data,bytes_transferred));
        return true;
}

bool CTcpAbstractSocket::writeDataed(std::size_t bytes_transferred,std::size_t willWriteSize)
{
    if(bytes_transferred == willWriteSize)
        Q_EMIT bytesWritten(bytes_transferred);
    return true;
}

void CTcpAbstractSocket::finedHosted()
{
    setState(ConnectingState);
    Q_EMIT hostFinded();
}
