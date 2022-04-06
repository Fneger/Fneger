#ifndef CGARBAGECOLLECTOR_H
#define CGARBAGECOLLECTOR_H

#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"
#include <QThread>
#include <vector>
#include <unordered_map>

class CAsioTcpSocket;
#ifdef USE_PROTOBUF
class CClientNode;
#else
namespace ExampleServer {
class st_clientNode_baseTrans;
}
#endif

class CGarbageCollector : public QThread
{
    Q_OBJECT
public:
    static CGarbageCollector *Instance();
    void startCollection();
    void stopCollection();
    void sockPutInTrash(boost::shared_ptr<CAsioTcpSocket> &garbage);
#ifdef USE_PROTOBUF
    void nodePutInTrash(boost::shared_ptr<CClientNode> &garbage);
    void nodePutInNoactive(boost::shared_ptr<CClientNode> &garbage);
#else
    void nodePutInTrash(boost::shared_ptr<ExampleServer::st_clientNode_baseTrans> &garbage);
    void nodePutInNoactive(boost::shared_ptr<ExampleServer::st_clientNode_baseTrans> &garbage);
#endif
    size_t sockTrashSize();
    size_t nodeTrashSize();
    size_t nodeNoactiveSize();
    boost::shared_ptr<CAsioTcpSocket> sockResumeRabish();
#ifdef USE_PROTOBUF
    boost::shared_ptr<CClientNode> nodeResumeRabish();
    boost::shared_ptr<CClientNode> findNodeNoactive(qint64 nId);
#else
    boost::shared_ptr<ExampleServer::st_clientNode_baseTrans> nodeResumeRabish();
    boost::shared_ptr<ExampleServer::st_clientNode_baseTrans> findNodeNoactive(quint64 nId);
#endif

Q_SIGNALS:

public Q_SLOTS:

protected:
    void run();

private:
    explicit CGarbageCollector(QObject *parent = nullptr);
    static const int S_GARBAGE_LIVE_TIME = 30;
    static const int S_ACTIVE_TIMEOUT = 90;
    static CGarbageCollector *S_pThis;
    std::list<boost::shared_ptr<CAsioTcpSocket>> m_sock_trash;
#ifdef USE_PROTOBUF
    std::list<boost::shared_ptr<CClientNode>> m_node_trash;
    std::unordered_map<quint64, boost::shared_ptr<CClientNode>> m_node_noactive;
#else
    std::list<boost::shared_ptr<ExampleServer::st_clientNode_baseTrans>> m_node_trash;
    std::unordered_map<quint64, boost::shared_ptr<ExampleServer::st_clientNode_baseTrans>> m_node_noactive;
#endif
    boost::mutex m_sock_trash_mutex;
    boost::mutex m_node_trash_mutex;
    boost::mutex m_node_noactive_mutex;
    volatile bool m_quit_flag;
};

#endif // CGARBAGECOLLECTOR_H
