#ifndef ST_CLIENT_FILE_H
#define ST_CLIENT_FILE_H

#include <QMutex>
#include <QString>
#include <QJsonDocument>
#include "st_message.h"

namespace BdUgdServer {
class st_client_file
{
public:
    static st_client_file *Instance();
    //�򿪲�Ʒ��Ϣ�ļ�
    bool openProductJson(QJsonDocument &doc);
    //�����Ʒ��Ϣ�ļ�
    bool saveProductJson(QJsonDocument &doc);
    //���û���Ȩ��Ϣ�ļ�
    bool openAuthUsers(QJsonDocument &doc);
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

private:
    st_client_file();

    static st_client_file *S_pThis;
    //�����Ʒ�����Ϣ
    QString m_sProductInfosJson;
    QMutex m_mProductMutex;
    QMutex m_mAuthList;
};
}


#endif // ST_CLIENT_FILE_H
