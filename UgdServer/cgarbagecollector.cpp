#include "cgarbagecollector.h"
#include <QDateTime>
#include "casiotcpsocket.h"
#ifdef USE_PROTOBUF
#include "cclientnode.h"
#else
#include "st_clientnode_basetrans.h"

using namespace ExampleServer;
#endif


CGarbageCollector *CGarbageCollector::S_pThis = new CGarbageCollector;
CGarbageCollector::CGarbageCollector(QObject *parent)
    : QThread(parent)
    , m_quit_flag(true)
{

}

CGarbageCollector *CGarbageCollector::Instance()
{
    static boost::mutex s_mutex;
    boost::mutex::scoped_lock lock(s_mutex);
    return S_pThis;
}

void CGarbageCollector::sockPutInTrash(TcpSocketPtr &garbage)
{
    garbage->updateActiveTime();
    boost::mutex::scoped_lock lock(m_sock_trash_mutex);
    m_sock_trash.push_back(garbage);
}

void CGarbageCollector::nodePutInTrash(NodePtr &garbage)
{
    garbage->updateActiveTime();
    boost::mutex::scoped_lock lock(m_node_trash_mutex);
    m_node_trash.push_back(garbage);
}

void CGarbageCollector::nodePutInNoactive(NodePtr &garbage)
{
    garbage->updateActiveTime();
    garbage->setClientSock(nullptr);
    boost::mutex::scoped_lock lock(m_node_noactive_mutex);
    m_node_noactive[garbage->uuid()] = garbage;
}

size_t CGarbageCollector::sockTrashSize()
{
    boost::mutex::scoped_lock lock(m_sock_trash_mutex);
    return m_sock_trash.size();
}

size_t CGarbageCollector::nodeTrashSize()
{
    boost::mutex::scoped_lock lock(m_node_trash_mutex);
    return m_node_trash.size();
}

size_t CGarbageCollector::nodeNoactiveSize()
{
    boost::mutex::scoped_lock lock(m_node_noactive_mutex);
    return m_node_noactive.size();
}

NodePtr CGarbageCollector::findNodeNoactive(quint64 nId)
{
    boost::mutex::scoped_lock lock(m_node_noactive_mutex);
    NodePtr pNode;
    if(m_node_noactive.find(nId) != m_node_noactive.end())
    {
        pNode = m_node_noactive[nId];
        if(pNode->uuid() != nId)
        {
            return NodePtr();
        }
        m_node_noactive.erase(nId);
    }
    return pNode;
}


void CGarbageCollector::startCollection()
{
    m_quit_flag = false;
    this->start();
}

void CGarbageCollector::stopCollection()
{
    m_quit_flag = true;
    this->quit();
    this->wait();

    {
        boost::mutex::scoped_lock lock(m_sock_trash_mutex);
        m_sock_trash.clear();
    }

    {
        boost::mutex::scoped_lock lock(m_node_trash_mutex);
        m_node_trash.clear();
    }
}

TcpSocketPtr CGarbageCollector::sockResumeRabish()
{
    TcpSocketPtr pSock;
    boost::mutex::scoped_lock lock(m_sock_trash_mutex);
    if(!m_sock_trash.empty())
    {
        pSock = m_sock_trash.front();
        m_sock_trash.pop_front();
    }
    return pSock;
}

NodePtr CGarbageCollector::nodeResumeRabish()
{
    NodePtr pNode;
    boost::mutex::scoped_lock lock(m_node_trash_mutex);
    if(!m_node_trash.empty())
    {
        pNode = m_node_trash.front();
        pNode->resetNode();
        m_node_trash.pop_front();
    }
    return pNode;
}

void CGarbageCollector::run()
{
    qint64 currSec = QDateTime::currentSecsSinceEpoch();
    while (1) {
        if(m_quit_flag)
            break;

        currSec = QDateTime::currentSecsSinceEpoch();
        do
        {
            msleep(10);
            boost::mutex::scoped_lock lock(m_sock_trash_mutex);
            if(!m_sock_trash.empty())
            {
                TcpSocketPtr &pSock = m_sock_trash.front();
                if(currSec - pSock->activeTime() > S_GARBAGE_LIVE_TIME)
                    m_sock_trash.pop_front();
                else
                    break;
            }
            else
                break;
        }while(1);

        currSec = QDateTime::currentSecsSinceEpoch();
        do
        {
            msleep(10);
            boost::mutex::scoped_lock lock(m_node_trash_mutex);
            if(!m_node_trash.empty())
            {
                NodePtr &pNode = m_node_trash.front();
                if(currSec - pNode->activeTime() > S_GARBAGE_LIVE_TIME)
                    m_node_trash.pop_front();
                else
                    break;
            }
            else
                break;
        }while(1);

        {
            std::vector<NodePtr> delNodes;
            NodePtr pNode;
            std::unordered_map<quint64, NodePtr>::iterator it;

            {
                boost::mutex::scoped_lock lock(m_node_noactive_mutex);
                for(it = m_node_noactive.begin(); it != m_node_noactive.end(); ++it){
                    pNode = (*it).second;
                    if(pNode == nullptr)
                        delNodes.push_back(pNode);
                    else if (pNode->ref() ==0 && currSec - pNode->activeTime() > S_ACTIVE_TIMEOUT)
                        delNodes.push_back(pNode);

                }
            }
            foreach (NodePtr pNode, delNodes) {
                msleep(10);
                nodePutInTrash(pNode);
                boost::mutex::scoped_lock lock(m_node_noactive_mutex);
                m_node_noactive.erase(pNode->uuid());
            }
            delNodes.clear();
        }
        msleep(10000);
    }
}
