#ifndef ST_CLIENT_EVENT_H
#define ST_CLIENT_EVENT_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QJsonDocument>
#include "st_message.h"
#include <unordered_map>
#include <unordered_map>

using namespace std;
namespace BdUgdServer {
class st_client_event : public QObject
{
    Q_OBJECT
public:
    static st_client_event *Instance();
    //���/�Ƴ� �¼�
    void AddClientEvent(EVENT_INFO_S &eventInfo);
    bool RemoveClientEvent(quint64 eventSn);
    void RemoveClientAllEvent();
    //��ȡuuid�û������¼�
    QMap<quint64,EVENT_INFO_S> GetUuidEvents(uint64_t nUuid);

    //��ѯ�¼�
    QMap<quint64,EVENT_INFO_S> GetTerminalEvents(const TERMINAL_INFO_S &tmnInfo);
    int GetEventStatus(quint64 eventSn);
    void SetEventStatus(BD_REQUEST_SET_EVENT_STATUS_S status);

Q_SIGNALS:

public slots:

private:
    explicit st_client_event(QObject *parent = nullptr);
    ~st_client_event();
    std::unordered_map<quint64,EVENT_INFO_S> m_events;
    QMutex m_eventsMutex;
    quint64 m_eventSnRef;
};
}


#endif // ST_CLIENT_EVENT_H
