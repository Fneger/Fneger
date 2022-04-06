#include "casiodatabase.h"
#include <QSqlQuery>
#include "st_message.h"
#include "st_client_table.h"

using namespace BdUgdServer;
static const QString S_ERR_STR_NOT_OPEN = "Database(%1) is not open";
ExampleServer::st_client_table * CAsioDatabase::s_client_table_ = nullptr;
CAsioDatabase *CAsioDatabase::S_pThis = new CAsioDatabase;
CAsioDatabase::CAsioDatabase()
{
     io_svr_.reset(new IOServiceClass(boost::thread::hardware_concurrency()));
}

CAsioDatabase::~CAsioDatabase()
{
    io_svr_->stop();
}

CAsioDatabase *CAsioDatabase::Instance()
{
    return S_pThis;
}

void CAsioDatabase::putDb2Struct(GS_BODY_TYPE nType, GS_DB_BODY_C &body, const QSqlQuery &query)
{
    //此处字段顺序必须与数据库中定义顺序对应
    switch (nType) {
    case TB_USERS_INFO_E:
    {
        USER_INFO_S info;
        info.id = query.value(0).toInt();
        info.name = query.value(1).toString();
        info.auth = query.value(2).toInt();
        info.date = query.value(3).toString();
        info.password = query.value(4).toString();
        info.products = query.value(5).toString().split(",");
        info.log_path = query.value(6).toString();
        info.auth_bits = query.value(7).toLongLong();
        info.message = query.value(8).toString();
        body = info;
    }
        break;
    case TB_PRODUCTS_INFO_E:
    {
        BODY_PRODUCT_INFO_S info;
        info.id = query.value(0).toInt();
        info.name = query.value(1).toString();
        info.desp = query.value(2).toString();
        info.addDate = query.value(3).toString();
        info.modifyDate = query.value(4).toString();
        info.savePath = query.value(5).toString();
        body = info;
    }
        break;
    case TB_CRC_VERSION_INFO_E:
    {
        BODY_CRC_VERSION_INFO_S info;
        info.id = query.value(0).toInt();
        info.productName = query.value(1).toString();
        info.name = query.value(2).toString();
        info.date = query.value(3).toString();
        info.isDefaultVersion = query.value(4).toBool();
        info.message = query.value(5).toString();
        info.fileName = query.value(6).toString();
        info.fileSize = query.value(7).toUInt();
        info.custom = query.value(8).toString();
        body = info;
    }
        break;
    case TB_MCU_VERSION_INFO_E:
    {
        BODY_MCU_VERSION_INFO_S info;
        info.id = query.value(0).toInt();
        info.productName = query.value(1).toString();
        info.mcuTypeName = query.value(2).toString();
        info.name = query.value(3).toString();
        info.date = query.value(4).toString();
        info.isDefaultVersion = query.value(5).toBool();
        info.message = query.value(6).toString();
        info.fileName = query.value(7).toString();
        info.fileSize = query.value(8).toUInt();
        body = info;
    }
        break;
    case TB_GROUP_VERSION_INFO_E:
    {
        BODY_GROUP_VERSION_INFO_S info;
        info.id = query.value(0).toInt();
        info.productName = query.value(1).toString();
        info.name = query.value(2).toString();
        info.date = query.value(3).toString();
        info.isDefaultVersion = query.value(4).toBool();
        info.message = query.value(5).toString();
        info.savePath = query.value(6).toString();
        info.subFileName = query.value(7).toString();
        info.subFileDate = query.value(8).toString();
        info.subFilePath = query.value(9).toString();
        info.subFileSize = query.value(10).toUInt();
        info.subFileMessage = query.value(11).toString();
        body = info;
    }
        break;
    case TB_LOG_INFO_E:
    {
        BODY_LOG_INFO_S info;
        info.id = query.value(0).toInt();
        info.productName = query.value(1).toString();
        info.devNumber = query.value(2).toString();
        info.imeiNumber = query.value(3).toString();
        info.fwVersion = query.value(4).toString();
        info.type = (GS_LOG_TYPE)query.value(5).toInt();
        info.subtype = query.value(6).toInt();
        info.result = (GS_LOG_RESULT)query.value(7).toInt();
        info.dateTime = query.value(8).toDateTime();
        info.serverDateTime = query.value(9).toDateTime();
        info.message = query.value(10).toString();
        body = info;
    }
        break;
    case TB_TMN_INFO_LOG_INFO_E:
    {
        BODY_TMN_INFO_S info;
        info.id = query.value(0).toInt();
        info.productName = query.value(1).toString();
        info.deviceNum = query.value(2).toString();
        info.phoneNumber = query.value(3).toString();
        info.licenseNum = query.value(4).toString();
        info.videoId = query.value(5).toString();
        info.terminalId = query.value(6).toString();
        info.imeiNumber = query.value(7).toString();
        info.crcVersion = query.value(8).toString();
        info.mcuVersion = query.value(9).toString();
        info.authorizationStatus = query.value(10).toInt();
        info.serverInfos.clear();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(query.value(11).toString().toUtf8(),&err);
        if (QJsonParseError::NoError != err.error)
        {
            QJsonArray serverInfos = doc.array();
            foreach (QJsonValue val, serverInfos) {
                QJsonObject serverInfoObj = val.toObject();
                if(!serverInfoObj.contains("IpAddr") || !serverInfoObj.contains("Port"))
                    break;
                BODY_SERVER_INFO_S serverInfo;
                serverInfo.ipAddr = serverInfoObj["IpAddr"].toString();
                serverInfo.port = serverInfoObj["Port"].toInt();
                info.serverInfos << serverInfo;
            }
        }
        info.dateTime = query.value(8).toDateTime();
        info.serverDateTime = query.value(9).toDateTime();
        body = info;
    }
        break;
    }
}

void CAsioDatabase::putDb2Struct(QueryCode nCode, GS_DB_BODY_C &body, const QSqlQuery &query)
{
    //此处字段顺序必须与数据库中定义顺序对应
    switch (nCode) {
    case QueryDefaultVersion:
    {
        BODY_CRC_VERSION_INFO_S info;
        info.productInfo.name =  query.value(0).toString();
        info.productInfo.savePath = query.value(1).toString();
        info.productName = info.productInfo.name;
        info.name = query.value(2).toString();
        info.date = query.value(3).toString();
        info.isDefaultVersion = query.value(4).toBool();
        info.message = query.value(5).toString();
        info.fileName = query.value(6).toString();
        info.fileSize = query.value(7).toUInt();
        info.custom = query.value(8).toString();
        body = info;
    }
        break;
    }
}

void CAsioDatabase::queryItem(QUERY_DB_PARAMS_S &params)
{
    params.db = s_client_table_->dbRes()->databse(s_client_table_->Database_UserAcct());
    if(params.nType >= TB_TYPE_MAX || params.nType < 0)
    {
        qDebug() << "Unsupported structure type" << params.nType << __FUNCTION__;
        params.callback(params);
    }
    QString sql;
    if (params.db.isValid()==true && params.db.isOpen()==true )
    {
        QSqlQuery query(params.db);

        switch (params.nType) {
        case TB_USERS_INFO_E:
        {
            USER_INFO_S body =  boost::any_cast<USER_INFO_S>(params.dbBody);
            sql = QString("SELECT * FROM %1 WHERE name = ?;").arg(S_USERS_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(body.name);
            if (true==query.exec())
            {
                if (query.next())
                {
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    params.dbBody = tBody;
                    params.result = true;
                }
                else
                    params.tips = QString("Query user info failed,%1").arg(body.name);
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_PRODUCTS_INFO_E:
        {
            BODY_PRODUCT_INFO_S body =  boost::any_cast<BODY_PRODUCT_INFO_S>(params.dbBody);
            sql = QString("SELECT * FROM %1 WHERE name = ?;").arg(S_PRODUCTS_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(body.name);
            if (true==query.exec())
            {
                if (query.next())
                {
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    params.dbBody = tBody;
                    params.result = true;
                }
                else
                    params.tips = QString("Query products info failed,%1").arg(body.name);
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_CRC_VERSION_INFO_E:
        {
            BODY_CRC_VERSION_INFO_S body =  boost::any_cast<BODY_CRC_VERSION_INFO_S>(params.dbBody);
            sql = QString("SELECT * FROM %1 WHERE name = ? AND product_name = ?;").arg(S_CRC_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(body.name);
            query.addBindValue(body.productName);
            if (true==query.exec())
            {
                if (query.next())
                {
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    params.dbBody = tBody;
                    params.result = true;
                }
                else
                    params.tips = QString("Query user info failed,%1").arg(body.name);
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_MCU_VERSION_INFO_E:
        {
            BODY_MCU_VERSION_INFO_S body =  boost::any_cast<BODY_MCU_VERSION_INFO_S>(params.dbBody);
            sql = QString("SELECT * FROM %1 WHERE name = ? AND product_name = ? AND mcu_type_name=?;").arg(S_MCU_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(body.name);
            query.addBindValue(body.productName);
            query.addBindValue(body.mcuTypeName);
            if (true==query.exec())
            {
                if (query.next())
                {
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    params.dbBody = tBody;
                    params.result = true;
                }
                else
                    params.tips = QString("Query user info failed,%1").arg(body.name);
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_GROUP_VERSION_INFO_E:
        {
            BODY_GROUP_VERSION_INFO_S body =  boost::any_cast<BODY_GROUP_VERSION_INFO_S>(params.dbBody);
            sql = QString("SELECT * FROM %1 WHERE name = ? AND product_name = ?;").arg(S_GROUP_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(body.name);
            query.addBindValue(body.productName);
            if (true==query.exec())
            {
                if (query.next())
                {
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    params.dbBody = tBody;
                    params.result = true;
                }
                else
                    params.tips = QString("Query user info failed,%1").arg(body.name);
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        }
    }
    else
        params.tips = QString(S_ERR_STR_NOT_OPEN).arg(params.db.databaseName());
    if(params.result)
    {
        params.callback(params);
        return;
    }
__SQL_QUERY_FAILED:
    params.tips = QString("Failed to execute mysql command,%1").arg(sql);
    if(!params.result)
        qDebug() << params.tips;
    params.callback(params);
}

void CAsioDatabase::queryItems(QUERY_DB_PARAMS_S &params)
{
    params.db = s_client_table_->dbRes()->databse(s_client_table_->Database_UserAcct());
    if(params.nType >= TB_TYPE_MAX || params.nType < 0)
    {
        qDebug() << "Unsupported structure type" << params.nType << __FUNCTION__;
        params.callback(params);
    }
    QString sql;
    if (params.db.isValid()==true && params.db.isOpen()==true )
    {
        QSqlQuery query(params.db);

        switch (params.nType) {
        case TB_USERS_INFO_E:
        {
            sql = QString("SELECT * FROM %1 LIMIT ?,?;").arg(S_USERS_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(params.startId);
            query.addBindValue(params.nItemCntMax);
            if (true==query.exec())
            {
                QList<USER_INFO_S> items = boost::any_cast<QList<USER_INFO_S>>(params.dbBodys);
                items.clear();

                while (query.next()) {
                    USER_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    body = boost::any_cast<USER_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all user info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_PRODUCTS_INFO_E:
        {
            sql = QString("SELECT * FROM %1 LIMIT ?,?;").arg(S_PRODUCTS_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(params.startId);
            query.addBindValue(params.nItemCntMax);
            if (true==query.exec())
            {
                QList<BODY_PRODUCT_INFO_S> items = boost::any_cast<QList<BODY_PRODUCT_INFO_S>>(params.dbBodys);
                items.clear();
                while (query.next()) {
                    //此处字段顺序必须与数据库中定义顺序对应
                    BODY_PRODUCT_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    body = boost::any_cast<BODY_PRODUCT_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all products info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_CRC_VERSION_INFO_E:
        {
            sql = QString("SELECT * FROM %1 LIMIT ?,?;").arg(S_CRC_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(params.startId);
            query.addBindValue(params.nItemCntMax);
            if (true==query.exec())
            {
                QList<BODY_CRC_VERSION_INFO_S> items = boost::any_cast<QList<BODY_CRC_VERSION_INFO_S>>(params.dbBodys);
                items.clear();
                while (query.next()) {
                    BODY_CRC_VERSION_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    body = boost::any_cast<BODY_CRC_VERSION_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all crc version info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_MCU_VERSION_INFO_E:
        {
            sql = QString("SELECT * FROM %1 LIMIT ?,?;").arg(S_MCU_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(params.startId);
            query.addBindValue(params.nItemCntMax);
            if (true==query.exec())
            {
                QList<BODY_MCU_VERSION_INFO_S> items = boost::any_cast<QList<BODY_MCU_VERSION_INFO_S>>(params.dbBodys);
                items.clear();
                while (query.next()) {
                    BODY_MCU_VERSION_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    body = boost::any_cast<BODY_MCU_VERSION_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all mcu version info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        case TB_GROUP_VERSION_INFO_E:
        {
            sql = QString("SELECT * FROM %1 LIMIT ?,?;").arg(S_GROUP_VERSION_INFO_TABLE_NAME);
            query.prepare(sql);
            query.addBindValue(params.startId);
            query.addBindValue(params.nItemCntMax);
            if (true==query.exec())
            {
                QList<BODY_GROUP_VERSION_INFO_S> items = boost::any_cast<QList<BODY_GROUP_VERSION_INFO_S>>(params.dbBodys);
                items.clear();
                while (query.next()) {
                    BODY_GROUP_VERSION_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.nType, tBody, query);
                    body = boost::any_cast<BODY_GROUP_VERSION_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all group version info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        }
    }
    else
        params.tips = QString(S_ERR_STR_NOT_OPEN).arg(params.db.databaseName());
    if(params.result)
    {
        params.callback(params);
        return;
    }
__SQL_QUERY_FAILED:
    params.tips = QString("Failed to execute mysql command,%1").arg(sql);
    if(!params.result)
        qDebug() << params.tips;
    params.callback(params);
}

void CAsioDatabase::joinQueryItems(QUERY_DB_PARAMS_S params)
{
    params.db = s_client_table_->dbRes()->databse(s_client_table_->Database_UserAcct());
    QString sql;
    if (params.db.isValid()==true && params.db.isOpen()==true )
    {
        QSqlQuery query(params.db);

        switch (params.queryCode) {
        case fneger::QueryDefaultVersion:
        {
            QUERY_DEFAULT_VERSION_S queryBody = boost::any_cast<QUERY_DEFAULT_VERSION_S>(params.queryBody);
            sql = QString("SELECT a.name,a.save_path,b.name,b.date,"
                          "b.is_default_version,b.message,b.file_name,b.file_size,b.custom "
                          "FROM %1 a "
                          "JOIN %2 b "
                          "ON b.product_name=\"%3\" AND a.name=b.product_name AND b.is_default_version = TRUE;")
                    .arg(S_PRODUCTS_INFO_TABLE_NAME)
                    .arg(S_CRC_VERSION_INFO_TABLE_NAME)
                    .arg(queryBody.productName);
            query.prepare(sql);
            if (true==query.exec())
            {
                QList<BODY_CRC_VERSION_INFO_S> items;
                items.clear();
                while (query.next()) {
                    BODY_CRC_VERSION_INFO_S body;
                    GS_DB_BODY_C tBody;
                    putDb2Struct(params.queryCode, tBody, query);
                    body = boost::any_cast<BODY_CRC_VERSION_INFO_S>(tBody);
                    items << body;
                    params.result = true;
                }
                if(!params.result)
                    params.tips = QString("Query all crc version info failed");
                params.dbBodys = items;
            }
            else
                goto __SQL_QUERY_FAILED;
        }
            break;
        default:
            break;
        }
    }
    else
        params.tips = QString(S_ERR_STR_NOT_OPEN).arg(params.db.databaseName());
    if(params.result)
    {
        params.callback(params);
        return;
    }
__SQL_QUERY_FAILED:
    params.tips = QString("Failed to execute mysql command,%1").arg(sql);
    if(!params.result)
        qDebug() << params.tips;
    params.callback(params);
}
