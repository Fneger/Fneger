#ifndef QBOOSTASIOTCPSOCKET_H
#define QBOOSTASIOTCPSOCKET_H

#include <QObject>

class QBoostAsioTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit QBoostAsioTcpSocket(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QBOOSTASIOTCPSOCKET_H
