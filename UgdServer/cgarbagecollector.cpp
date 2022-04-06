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

void CGarbageCollector::sockPutInTrash(boost::shared_ptr<CAsioTcpSocket> &garbage)
{
    garbage->updateActiveTime();
    boost::mutex::scoped_lock lock(m_sock_trash_mutex);
    m_sock_trash.push_back(garbage);
}

#ifdef USE_PROTOBUF
void CGarbageCollector::nodePutInTrash(boost::shared_ptr<CClientNode> &garbage)
#else
void CGarbageCollector::nodePutInTrash(boost::shared_ptr<st_clientNode_baseTrans> &garbage)
#endif
{
    garbage->updateActiveTime();
    boost::mutex::scoped_lock lock(m_node_trash_mutex);
    m_node_trash.push_back(garbage);
}

#ifdef USE_PROTOBUF
void CGarbageCollector::nodePutInNoactive(boost::shared_ptr<CClientNode> &garbage)
#else
void CGarbageCollector::nodePutInNoactive(boost::shared_ptr<st_clientNode_baseTrans> &garbage)
#endif
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

#ifdef USE_PROTOBUF
boost::shared_ptr<CClientNode> CGarbageCollector::findNodeNoactive(qint64 nId)
#else
boost::shared_ptr<st_clientNode_baseTrans> CGarbageCollector::findNodeNoactive(quint64 nId)
#endif
{
    boost::mutex::scoped_lock lock(m_node_noactive_mutex);
#ifdef USE_PROTOBUF
    boost::shared_ptr<CClientNode> pNode;
#else
    boost::shared_ptr<st_clientNode_baseTrans> pNode;
#endif
    if(m_node_noactive.find(nId) != m_node_noactive.end())
    {
        pNode = m_node_noactive[nId];
        if(pNode->uuid() != nId)
        {
#ifdef USE_PROTOBUF
            return boost::shared_ptr<CClientNode>();
#else
            return boost::shared_ptr<st_clientNode_baseTrans>();
#endif
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

boost::shared_ptr<CAsioTcpSocket> CGarbageCollector::sockResumeRabish()
{
    boost::shared_ptr<CAsioTcpSocket> pSock;
    boost::mutex::scoped_lock lock(m_sock_trash_mutex);
    if(m_sock_trash.size() > 0)
    {
        pSock = m_sock_trash.front();
        m_sock_trash.pop_front();
    }
    return pSock;
}

#ifdef USE_PROTOBUF
boost::shared_ptr<CClientNode> CGarbageCollector::nodeResumeRabish()
#else
boost::shared_ptr<ExampleServer::st_clientNode_baseTrans> CGarbageCollector::nodeResumeRabish()
#endif
{
#ifdef USE_PROTOBUF
    boost::shared_ptr<CClientNode> pNode;
#else
    boost::shared_ptr<st_clientNode_baseTrans> pNode;
#endif
    boost::mutex::scoped_lock lock(m_node_trash_mutex);
    if(m_node_trash.size() > 0)
    {
        pNode = m_node_trash.front();
        pNode->resetNode();
        m_node_trash.pop_front();
    }
    return pNode;
}

void CGarbageCollector::run()
{
    size_t trashSize;
    qint64 currSec = QDateTime::currentSecsSinceEpoch();
    while (1) {
        if(m_quit_flag)
            break;

        currSec = QDateTime::currentSecsSinceEpoch();
        do
        {
            msleep(10);
            boost::mutex::scoped_lock lock(m_sock_trash_mutex);
            trashSize = m_sock_trash.size();
            if(trashSize > 0)
            {
                boost::shared_ptr<CAsioTcpSocket> &pSock = m_sock_trash.front();
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
            trashSize = m_node_trash.size();
            if(trashSize > 0)
            {
#ifdef USE_PROTOBUF
                boost::shared_ptr<CClientNode> &pNode = m_node_trash.front();
#else
                boost::shared_ptr<st_clientNode_baseTrans> &pNode = m_node_trash.front();
#endif
                if(currSec - pNode->activeTime() > S_GARBAGE_LIVE_TIME)
                    m_node_trash.pop_front();
                else
                    break;
            }
            else
                break;
        }while(1);

        {
#ifdef USE_PROTOBUF
            std::vector<boost::shared_ptr<CClientNode>> delNodes;
            boost::shared_ptr<CClientNode> pNode;
            std::unordered_map<quint64, boost::shared_ptr<CClientNode>>::iterator it;
#else
            std::vector<boost::shared_ptr<st_clientNode_baseTrans>> delNodes;
            boost::shared_ptr<st_clientNode_baseTrans> pNode;
            std::unordered_map<quint64, boost::shared_ptr<st_clientNode_baseTrans>>::iterator it;
#endif

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
#ifdef USE_PROTOBUF
            foreach (boost::shared_ptr<CClientNode> pNode, delNodes) {
#else
            foreach (boost::shared_ptr<st_clientNode_baseTrans> pNode, delNodes) {
#endif
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
