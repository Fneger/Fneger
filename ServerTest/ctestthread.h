#ifndef CTESTTHREAD_H
#define CTESTTHREAD_H

#include <QThread>

class CTestThread : public QThread
{
    Q_OBJECT
public:
    explicit CTestThread(QObject *parent = nullptr);

Q_SIGNALS:

public Q_SLOTS:

protected:
    void run();

private:

};

#endif // CTESTTHREAD_H
