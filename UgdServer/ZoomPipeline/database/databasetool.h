#ifndef DATABASETOOL_H
#define DATABASETOOL_H

#include <QObject>
#include <QMutex>
#include <QSqlDatabase>
#include "st_message.h"
#include "st_global_def.h"

using namespace GsGlobalDef;
using namespace BdUgdServer;

namespace ZPDatabase {

class DatabaseTool : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseTool(QObject *parent = nullptr);
    ~DatabaseTool();
    QString getLogTableName(const QString &devNumber);
    QString getLogTableName(int devNumber);
    static bool logTableExists(QSqlDatabase db, const QString &devNumber, bool isTmnInfo = false);
    static void setLogTableExists(QSqlDatabase db, const QString &devNumber, bool bExists, bool isTmnInfo = false);
    //�ж����ݿ��Ƿ����
    bool schemataExists(QSqlDatabase db, const QString &dbName);
    //�ж����ݰ����Ƿ����
    bool tableExists(QSqlDatabase db, const QString &tableName);
    //�������ݱ�
    bool createTable(QSqlDatabase db, GS_BODY_TYPE nType, const QString &extTableName = "");
    //ɾ�����ݱ�ֱ��ɾ���������ݺͽṹ�����ã�������������������
    bool deleteTable(QSqlDatabase db, GS_BODY_TYPE nType, const QString &extTableName = "");
    //�����ݱ��в�������
    bool insertItem(QSqlDatabase db, GS_BODY_TYPE nType,const GS_DB_BODY_C &dbBody, const QString &extTableName = "");
    //ɾ�����ݱ���ĳһ��
    bool deleteItem(QSqlDatabase db, GS_BODY_TYPE nType, const GS_DB_BODY_C &dbBody);
    //�������ݱ���ĳһ��
    bool updateItem(QSqlDatabase db, GS_BODY_TYPE nType,const GS_DB_BODY_C &dbBody);
    //����������ѯ���ݱ�ĳһ��
    bool queryItem(QSqlDatabase db, GS_BODY_TYPE nType, GS_DB_BODY_C &dbBody);
    //��ȡ���ж��Ԫ��,���б���ṹ��ָ���ڴ�����ʹ�ú��ͷ�
    bool queryItems(QSqlDatabase db, GS_BODY_TYPE nType, GS_DB_BODY_C &dbBodys, const QString &extTableName = "", int startId = 0, int nItemCntMax = S_QUERY_ITEM_NUM_MAX);
    //���ݲ�����������ȡ��������
    bool queryItems(QSqlDatabase db, GS_BODY_TYPE nType, GS_DB_BODY_C &dbBodys, const QString &queryCondition, const QString &extTableName = "", int startId = 0, int nItemCntMax = S_QUERY_ITEM_NUM_MAX);
    //��ѯ��������������
    int queryMatchItemsCount(QSqlDatabase db, GS_BODY_TYPE nType, const QString &queryCondition, const QString &extTableName = "");
    //��ȡ������������
    int queryItemsCount(QSqlDatabase db, GS_BODY_TYPE nType);
    QString errInfo();
    //�������ݱ���չ����
    //void setExtTableName(const QString &name) { m_extTableName = name; }

private:
    //��ʼ����־�����
    static bool initLogTableManager(QSqlDatabase db, int devNum, bool isTmnInfo = false);
    QString strListToStrs(const QStringList &list);
    void putDb2Struct(GS_BODY_TYPE nType, GS_DB_BODY_C &body, const QSqlQuery &query);


signals:

public slots:

private:
    QString m_errInfo;
    //QString m_extTableName; //���ݱ���չ����
    static QMap<int, LOG_TABLE_MAN_S> m_logTableManager;
    static QMap<int, LOG_TABLE_MAN_S> m_tmnInfoLogTableManager;
    static QMutex m_logManMutex;
};
}

#endif // DATABASETOOL_H
