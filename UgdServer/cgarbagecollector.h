#ifndef CGARBAGECOLLECTOR_H
#define CGARBAGECOLLECTOR_H

#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"
#include <QThread>
#include <vector>
#include <unordered_map>
#include "st_client_table.h"

class CAsioTcpSocket;
#ifdef USE_PROTOBUF
class CClientNode;
#else
namespace ExampleServer {
class st_clientNode_baseTrans;
}
#endif

using namespace ExampleServer;

class CGarbageCollector : public QThread
{
    Q_OBJECT
public:
    static CGarbageCollector *Instance();
    void startCollection();
    void stopCollection();
    void sockPutInTrash(TcpSocketPtr &garbage);
    void nodePutInTrash(NodePtr &garbage);
    void nodePutInNoactive(NodePtr &garbage);
    size_t sockTrashSize();
    size_t nodeTrashSize();
    size_t nodeNoactiveSize();
    TcpSocketPtr sockResumeRabish();
    NodePtr nodeResumeRabish();
    NodePtr findNodeNoactive(quint64 nId);

Q_SIGNALS:

public Q_SLOTS:

protected:
    void run();

private:
    explicit CGarbageCollector(QObject *parent = nullptr);
    static const int S_GARBAGE_LIVE_TIME = 30;
    static const int S_ACTIVE_TIMEOUT = 90;
    static CGarbageCollector *S_pThis;
    std::list<TcpSocketPtr> m_sock_trash;
    std::list<NodePtr> m_node_trash;
    UuidNodeContainer m_node_noactive;
    boost::mutex m_sock_trash_mutex;
    boost::mutex m_node_trash_mutex;
    boost::mutex m_node_noactive_mutex;
    volatile bool m_quit_flag;
};

#endif // CGARBAGECOLLECTOR_H
