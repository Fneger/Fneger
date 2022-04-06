#ifndef ST_CLIENT_FILE_H
#define ST_CLIENT_FILE_H

#include <QMutex>
#include <QString>
#include <QJsonDocument>
#include "st_message.h"
#include "st_client_table.h"
#include "st_global_def.h"
#include "databasetool.h"

using namespace GsGlobalDef;
using namespace ZPDatabase;

class st_client_table;
class QTimer;
namespace BdUgdServer {

class st_client_file
{
public:
    st_client_file();
    ~st_client_file();
    //�򿪲�Ʒ��Ϣ�ļ�
    bool openProductJson(const QString &fileName, QJsonDocument &doc);
    //�����ݿ��л�ȡ��Ʒ��Ϣ
    bool openProductDb(const QString &fileName, QJsonDocument &doc);
    //�����Ʒ��Ϣ�ļ�
    bool saveProductJson(const QString &fileName,QJsonDocument &doc);
    //�������
    bool addDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body);
    //ɾ������
    bool removeDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body);
    //�������ݿ�
    bool updateDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body);
    //��ѯ���ݿ�
    bool queryDb(GS_BODY_TYPE nType, GS_DB_BODY_C &body);
    bool queryDb(GS_BODY_TYPE nType, GS_DB_BODY_C &body, const QString &queryCondition);
    //ɾ����Ʒ
    bool removeProductDb(const QString &productName);
    //������־���ݱ�
    bool createLogTableDb(const QString &name, bool isTmnInfo = false);
    //ɾ����־���ݱ��ڲ�Ʒɾ�����ݲ�ɾ�������־����
    bool deleteLogTableDb(const QString &name, bool isTmnInfo = false);
    //�����־����
    bool addLogDb(const BODY_LOG_INFO_S &log);
    //����ն���Ϣ��־����
    bool addTmnInfoLogDb(const BODY_TMN_INFO_S &log);
    //��ѯ��־����,����ƥ����������
    bool queryLogDb(const QString &devNumber, GS_DB_BODY_C &body, const QString &queryCondition, bool isTmnInfo = false, int startId = 0, int nItemCntMax = S_QUERY_ITEM_NUM_MAX);
    //��ѯ����ƥ����������������
    int queryLogMatchCountDb(const QString &devNumber, const QString &queryCondition, bool isTmnInfo = false);


    //���û���Ȩ��Ϣ�ļ�
    bool openAuthUsers(QJsonDocument &doc);
    bool openAuthUsersDb(QJsonDocument &doc);
    //�����û���Ȩ��Ϣ�ļ�
    bool saveAuthUsers(QJsonDocument &doc);
    //�����Ȩ�û�
    bool addAuthUser(const USER_INFO_S &userInfo);
    //�Ƴ���Ȩ�û�
    bool removeAuthUser(const USER_INFO_S &userInfo);
    //�༭�û���Ϣ
    bool editAuthUser(const USER_INFO_S &userInfo);
    //�ͻ��˵�¼
    bool loginClient(const BD_TMN_LOGIN_INFO_S loginInfo, USER_INFO_S &userInfo);
    static void setClientTable(ExampleServer::st_client_table *pClient);
    //�����Ҫͬ��json�����ݿ�
    static void syncJson2Database();
    void putInfo2Json(GS_BODY_TYPE nType, const GS_DB_BODY_C &body, QJsonObject &infoObj);
    void putInfos2Json(GS_BODY_TYPE nType, const GS_DB_BODY_C &bodys, QJsonObject &infosObj);

private:
    void slot_bakTimerTimeout();


private:
    //�����Ʒ�����Ϣ
    QMutex m_mProductMutex;
    QMutex m_mAuthList;
    static ExampleServer::st_client_table * m_pClientTable;
    QScopedPointer<DatabaseTool> m_dbTool;
};
}


#endif // ST_CLIENT_FILE_H
