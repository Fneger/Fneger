#include "st_client_file.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "databaseresource.h"


using namespace ZPDatabase;

namespace BdUgdServer {
ExampleServer::st_client_table * st_client_file::m_pClientTable = nullptr;
st_client_file::st_client_file()
{
    m_dbTool.reset(new DatabaseTool());
}

st_client_file::~st_client_file()
{

}

void st_client_file::slot_bakTimerTimeout()
{

}

void st_client_file::putInfo2Json(GS_BODY_TYPE nType, const GS_DB_BODY_C &body, QJsonObject &infoObj)
{
    switch (nType) {
    case TB_PRODUCTS_INFO_E:
    {
        BODY_PRODUCT_INFO_S info = boost::any_cast<BODY_PRODUCT_INFO_S>(body);
    }
        break;
    case TB_CRC_VERSION_INFO_E:
    {
        BODY_CRC_VERSION_INFO_S info = boost::any_cast<BODY_CRC_VERSION_INFO_S>(body);
        infoObj["Name"] = info.name;
        infoObj["Date"] = info.date;
        infoObj["IsDefault"] = info.isDefaultVersion;
        infoObj["Message"] = info.message;
        infoObj["FileName"] = info.fileName;
        infoObj["FileSize"] = QString::number(info.fileSize);
        infoObj["Custom"] = GetCustom(info.name);
    }
        break;
    case TB_MCU_VERSION_INFO_E:
    {
        BODY_MCU_VERSION_INFO_S info = boost::any_cast<BODY_MCU_VERSION_INFO_S>(body);
        if(info.name.isEmpty() || info.name == "")
            return;
        infoObj["Name"] = info.name;
        infoObj["Date"] = info.date;
        infoObj["IsDefault"] = info.isDefaultVersion;
        infoObj["Message"] = info.message;
        infoObj["FileName"] = info.fileName;
        infoObj["FileSize"] = QString::number(info.fileSize);
    }
        break;
    case TB_GROUP_VERSION_INFO_E:
    {
        BODY_GROUP_VERSION_INFO_S info = boost::any_cast<BODY_GROUP_VERSION_INFO_S>(body);
        if(info.subFileName.isEmpty() || info.subFileName == "")
            return;
        infoObj["Name"] = info.subFileName;
        infoObj["Date"] = info.subFileDate;
        infoObj["IsDefault"] = info.isDefaultVersion;
        infoObj["Message"] = info.subFileMessage;
        infoObj["FileName"] = info.subFilePath;
        infoObj["FileSize"] = QString::number(info.subFileSize);
    }
        break;
    }
}

void st_client_file::putInfos2Json(GS_BODY_TYPE nType, const GS_DB_BODY_C &bodys, QJsonObject &infosObj)
{
    switch (nType) {
    case TB_GROUP_VERSION_INFO_E:
    {
        GS_DB_BODY_C body;
        QList<BODY_GROUP_VERSION_INFO_S> groupInfos = boost::any_cast<QList<BODY_GROUP_VERSION_INFO_S>>(bodys);
        foreach (BODY_GROUP_VERSION_INFO_S info, groupInfos) {
            QJsonObject groupFileObj;
            groupFileObj["Name"] = info.name;
            groupFileObj["Date"] = info.date;
            groupFileObj["SavePath"] = info.savePath;
            groupFileObj["Message"] = info.message;
            groupFileObj["IsDefault"] = info.isDefaultVersion;
            if(!infosObj.contains(info.name))
                infosObj[info.name] = groupFileObj;
            QJsonObject fileObj;
            body = info;
            putInfo2Json(TB_GROUP_VERSION_INFO_E, body, fileObj);
            if(!infosObj[info.name].toObject().contains("FileInfos"))
            {
                QJsonObject groupInfoObj = infosObj[info.name].toObject();
                QJsonArray fileArray;
                if(fileObj.size() > 0)
                    fileArray << fileObj;
                groupInfoObj["FileInfos"] = fileArray;
                infosObj[info.name] = groupInfoObj;
            }
            else
            {
                QJsonObject groupInfoObj = infosObj[info.name].toObject();
                QJsonArray fileArray = groupInfoObj["FileInfos"].toArray();
                if(fileObj.size() > 0)
                    fileArray << fileObj;
                groupInfoObj["FileInfos"] = fileArray;
                infosObj[info.name] = groupInfoObj;
            }
        }
    }
        break;
    default:
        qWarning() << "No surport type!";
        break;
    }
}

bool st_client_file::openProductJson(const QString &fileName,QJsonDocument &doc)
{
    bool res = false;
    QString strJson;
    m_mProductMutex.lock();
    QFile file(fileName);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        strJson = file.readAll();
        //qDebug() << "strJson" << strJson;
        res = true;
        if(file.size() > 10)
        {
            QJsonParseError err;
            doc = QJsonDocument::fromJson(strJson.toUtf8(),&err);
            if (QJsonParseError::NoError == err.error)
                res = true;
            else
                res = false;
        }
        file.close();
    }
    m_mProductMutex.unlock();
    return res;
}

bool st_client_file::openProductDb(const QString &fileName, QJsonDocument &doc)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    BODY_PRODUCT_INFO_S productInfo;
    productInfo.name = fileName;
    GS_DB_BODY_C body = productInfo;
    res = m_dbTool->queryItem(db, TB_PRODUCTS_INFO_E, body);
    if(res)
    {
        bool queryRes = false;
        productInfo = boost::any_cast<BODY_PRODUCT_INFO_S>(body);
        QJsonObject baseObj;
        QJsonObject productInfoObj;
        productInfoObj["ProductName"] = productInfo.name;
        productInfoObj["ProductTypeId"] = productInfo.id;
        productInfoObj["Date"] = productInfo.addDate;
        productInfoObj["ModifyDate"] = productInfo.modifyDate;
        productInfoObj["ProductDesp"] = productInfo.desp;
        productInfoObj["SaveFilePath"] = productInfo.savePath;

        GS_DB_BODY_C dbBody;

        //CRC
        bool isFillCrcDefaultVersion = false;
        QJsonArray crcDftVersionsArray;

        QList<BODY_CRC_VERSION_INFO_S> crcInfos;
        dbBody = crcInfos;
        QJsonArray crcVersionsArray;
        QString queryStr = QString("product_name = \"%1\"").arg(fileName);
        queryRes = m_dbTool->queryItems(db, TB_CRC_VERSION_INFO_E, dbBody, queryStr, "");
        if(queryRes)
        {
            crcInfos = boost::any_cast<QList<BODY_CRC_VERSION_INFO_S>>(dbBody);
            foreach (BODY_CRC_VERSION_INFO_S info, crcInfos) {
                QJsonObject infoObj;
                dbBody = info;
                putInfo2Json(TB_CRC_VERSION_INFO_E, dbBody, infoObj);
                if(info.isDefaultVersion)
                {
                    if(!isFillCrcDefaultVersion)
                    {
                        productInfoObj["CrcDefaultVersion"] = infoObj;
                        isFillCrcDefaultVersion = true;
                    }
                    crcDftVersionsArray << infoObj;
                }

                crcVersionsArray << infoObj;
            }
        }
        productInfoObj["CrcDefaultVersions"] = crcDftVersionsArray;
        productInfoObj["CrcVersionList"] = crcVersionsArray;

        //MCU
        QJsonArray mcuTypeArray;
        QList<BODY_MCU_VERSION_INFO_S> mcuVerInfos;
        dbBody = mcuVerInfos;
        queryStr = QString("product_name = \"%1\"").arg(fileName);
        queryRes = m_dbTool->queryItems(db, TB_MCU_VERSION_INFO_E, dbBody, queryStr, "");
        if(queryRes)
        {
            mcuVerInfos = boost::any_cast<QList<BODY_MCU_VERSION_INFO_S>>(dbBody);
            QJsonObject tMcuObj;
            foreach (BODY_MCU_VERSION_INFO_S info, mcuVerInfos) {
                QJsonObject mcuObj;
                dbBody = info;
                putInfo2Json(TB_MCU_VERSION_INFO_E, dbBody, mcuObj);
                if(!tMcuObj.contains(info.mcuTypeName))
                {
                    QJsonObject typeObj;
                    typeObj["McuTypeName"] = info.mcuTypeName;
                    typeObj["McuTypeId"] = 0;
                    tMcuObj[info.mcuTypeName] = typeObj;
                }
                QJsonObject typeObj = tMcuObj[info.mcuTypeName].toObject();
                if(info.isDefaultVersion)
                {
                    typeObj["McuDefaultVersion"] = mcuObj;
                    tMcuObj[info.mcuTypeName] = typeObj;
                }

                if(!typeObj.contains("McuVersionList"))
                {
                    QJsonArray mcuArray;
                    if(mcuObj.size() > 0)
                        mcuArray << mcuObj;
                    typeObj["McuVersionList"] = mcuArray;
                }
                else
                {
                    QJsonArray mcuArray = typeObj["McuVersionList"].toArray();
                    if(mcuObj.size() > 0)
                        mcuArray << mcuObj;
                    typeObj["McuVersionList"] = mcuArray;
                }

                tMcuObj[info.mcuTypeName] = typeObj;
            }
            foreach (QJsonValue value, tMcuObj) {
                mcuTypeArray << value.toObject();
            }
        }
        productInfoObj["McuInfos"] = mcuTypeArray;


        //GROUP
        QList<BODY_GROUP_VERSION_INFO_S> groupInfos;
        dbBody = groupInfos;
        QJsonArray groupFileArray;
        queryStr = QString("product_name = \"%1\"").arg(fileName);
        queryRes = m_dbTool->queryItems(db, TB_GROUP_VERSION_INFO_E, dbBody, queryStr, "");
        if(queryRes)
        {
            groupInfos = boost::any_cast<QList<BODY_GROUP_VERSION_INFO_S>>(dbBody);
            QJsonObject tGroupFileObj;
            putInfos2Json(TB_GROUP_VERSION_INFO_E, dbBody, tGroupFileObj);
            foreach (QJsonValue value, tGroupFileObj) {
                groupFileArray << value.toObject();
            }
        }
        productInfoObj["GroupFileInfos"] = groupFileArray;


        baseObj[fileName] = productInfoObj;
        doc.setObject(baseObj);
    }
    else
        qWarning() << "Failed to get product information from database!";
    return true;
}

bool st_client_file::addDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->insertItem(db, nType, body);
    if(!res)
        qWarning() << "Failed to add to database!";
    return res;
}

bool st_client_file::removeDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->deleteItem(db, nType, body);
    if(!res)
        qWarning() << "Failed to remove from database!";
    return res;
}

bool st_client_file::updateDb(GS_BODY_TYPE nType, const GS_DB_BODY_C &body)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->updateItem(db, nType, body);
    if(!res)
        qWarning() << "Failed to update database!";
    return res;
}

bool st_client_file::queryDb(GS_BODY_TYPE nType, GS_DB_BODY_C &body)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->queryItem(db, nType, body);
    if(!res)
        qWarning() << "Failed to query database!";
    return res;
}

bool st_client_file::queryDb(GS_BODY_TYPE nType, GS_DB_BODY_C &body, const QString &queryCondition)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->queryItems(db, nType, body, queryCondition, "");
    if(!res)
        qWarning() << "Failed to query database!";
    return res;
}

bool st_client_file::removeProductDb(const QString &productName)
{
    bool res = false;

    {
        BODY_CRC_VERSION_INFO_S info;
        info.productName = productName;
        GS_DB_BODY_C body = info;

        res = removeDb(TB_CRC_VERSION_INFO_E, body);
        if(!res)
            qWarning() << "Failed to delete product crc from database!";
    }

    {
        BODY_MCU_VERSION_INFO_S info;
        info.productName = productName;
        GS_DB_BODY_C body = info;

        res = removeDb(TB_MCU_VERSION_INFO_E, body);
        if(!res)
            qWarning() << "Failed to delete product mcu from database!";
    }

    {
        BODY_GROUP_VERSION_INFO_S info;
        info.productName = productName;
        GS_DB_BODY_C body = info;

        res = removeDb(TB_GROUP_VERSION_INFO_E, body);
        if(!res)
            qWarning() << "Failed to delete product group from database!";
    }

    BODY_PRODUCT_INFO_S info;
    info.name = productName;
    GS_DB_BODY_C body = info;

    res = removeDb(TB_PRODUCTS_INFO_E, body);
    if(!res)
        qWarning() << "Failed to delete product from database!";
    return res;
}

bool st_client_file::createLogTableDb(const QString &name, bool isTmnInfo)
{
    bool res = false;
    QString tbName = name.toLower() + "_" + S_LOG_INFO_TABLE_NAME;
    if(isTmnInfo)
        tbName = name.toLower() + "_" + S_TMN_INFO_LOG_INFO_TABLE_NAME;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    if(m_dbTool->tableExists(db, tbName))
    {
        qDebug() << "Log table exists." << tbName;
        return true;
    }
    if(isTmnInfo)
        res = m_dbTool->createTable(db, TB_TMN_INFO_LOG_INFO_E, name);
    else
        res = m_dbTool->createTable(db, TB_LOG_INFO_E, name);
    if(!res)
        qWarning() << "Create product log table failed!";
    return res;
}

bool st_client_file::deleteLogTableDb(const QString &name, bool isTmnInfo)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    if(isTmnInfo)
        res = m_dbTool->deleteTable(db, TB_TMN_INFO_LOG_INFO_E, name.toLower());
    else
        res = m_dbTool->deleteTable(db, TB_LOG_INFO_E, name.toLower());
    if(!res)
        qWarning() << "Remove product log table failed!";
    return res;
}

bool st_client_file::addLogDb(const BODY_LOG_INFO_S &log)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    QString tblName = m_dbTool->getLogTableName(log.devNumber);
    if(!m_dbTool->logTableExists(db, log.devNumber)) //���ݱ�δ���������������������
    {
        res = m_dbTool->createTable(db, TB_LOG_INFO_E, tblName);
        if(!res)
        {
            qWarning() << "Failed to create log table!" << tblName;
            return res;
        }
        m_dbTool->setLogTableExists(db, log.devNumber, true);
        qDebug() << "Created log table ok" << tblName;
    }
    GS_DB_BODY_C body = log;
    res = m_dbTool->insertItem(db, TB_LOG_INFO_E, body, tblName);

    if(!res)
        qWarning() << "Failed to add log to database!";
    return res;
}

bool st_client_file::addTmnInfoLogDb(const BODY_TMN_INFO_S &log)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    QString tblName = m_dbTool->getLogTableName(log.deviceNum);
    if(!m_dbTool->logTableExists(db, log.deviceNum, true)) //���ݱ�δ���������������������
    {
        res = m_dbTool->createTable(db, TB_TMN_INFO_LOG_INFO_E, tblName);
        if(!res)
        {
            qWarning() << "Failed to create log table!" << tblName;
            return res;
        }
        m_dbTool->setLogTableExists(db, log.deviceNum, true, true);
        qDebug() << "Created log table ok" << tblName;
    }
    GS_DB_BODY_C body = log;
    res = m_dbTool->insertItem(db, TB_TMN_INFO_LOG_INFO_E, body, tblName);

    if(!res)
        qWarning() << "Failed to add log to database!";
    return res;
}

bool st_client_file::queryLogDb(const QString &devNumber, GS_DB_BODY_C &body, const QString &queryCondition, bool isTmnInfo, int startId, int nItemCntMax)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    QString tblName = m_dbTool->getLogTableName(devNumber);
    if(isTmnInfo)
        res = m_dbTool->queryItems(db, TB_TMN_INFO_LOG_INFO_E, body, queryCondition, tblName, startId, nItemCntMax);
    else
        res = m_dbTool->queryItems(db, TB_LOG_INFO_E, body, queryCondition, tblName, startId, nItemCntMax);
    if(!res)
        qWarning() << "Failed to query log from database!";
    return res;
}

int st_client_file::queryLogMatchCountDb(const QString &devNumber, const QString &queryCondition, bool isTmnInfo)
{
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
     QString tblName = m_dbTool->getLogTableName(devNumber);
     if(isTmnInfo)
         return m_dbTool->queryMatchItemsCount(db, TB_TMN_INFO_LOG_INFO_E, queryCondition, tblName);
     else
         return m_dbTool->queryMatchItemsCount(db, TB_LOG_INFO_E, queryCondition, tblName);
}

bool st_client_file::saveProductJson(const QString &fileName,QJsonDocument &doc)
{
    m_mProductMutex.lock();
    QByteArray byte_array = doc.toJson(QJsonDocument::Indented);
    QString json_str(byte_array);
    //����ʵ����д·��
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "file error!";
        m_mProductMutex.unlock();
        return false;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    in << json_str;
    in.setGenerateByteOrderMark(false);

    file.close();   // �ر�file
    m_mProductMutex.unlock();
    return true;
}

bool st_client_file::openAuthUsers(QJsonDocument &doc)
{
    bool res = false;
    QString strJson;
    m_mAuthList.lock();
    QFile file("authlist.json");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        strJson = file.readAll();
        file.close();
    }
    m_mAuthList.unlock();
    if(file.size() == 0)
        res = true;
    QJsonParseError err;
    doc = QJsonDocument::fromJson(strJson.toUtf8(),&err);
    if (QJsonParseError::NoError == err.error)
    {
        res = true;
    }
    return res;
}

bool st_client_file::openAuthUsersDb(QJsonDocument &doc)
{
    bool res = false;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    GS_DB_BODY_C bodys;
    QList<USER_INFO_S> items;
    bodys = items;
    res = m_dbTool->queryItems(db, TB_USERS_INFO_E, bodys);
    if(res)
    {
        QList<USER_INFO_S> items = boost::any_cast<QList<USER_INFO_S>>(bodys);

        QJsonObject baseObj;
        foreach (USER_INFO_S body, items) {
            QJsonObject dataObj;
            dataObj["Name"]  = body.name;
            dataObj["Password"] = body.password;
            dataObj["Auth"] = body.auth;
            dataObj["Date"] = body.date;
            dataObj["Message"] = body.message;
            QJsonArray productArray;
            foreach (QString str, body.products) {
                if(str == "")
                    continue;
                productArray << str;
            }
            dataObj["Products"] = productArray;
            dataObj["LogPath"] = body.log_path;
            dataObj["AuthBits"] = body.auth_bits;
            baseObj[body.name] = dataObj;
        }
        doc.setObject(baseObj);
    }
    else
        qDebug() << "Query User infos failed!";
     return res;
}

bool st_client_file::saveAuthUsers(QJsonDocument &doc)
{
    bool res = false;
    QByteArray byte_array = doc.toJson(QJsonDocument::Indented);
    QString json_str(byte_array);
    //����ʵ����д·��
    m_mAuthList.lock();
    QFile file("authlist.json");

    if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        in << json_str;
        in.setGenerateByteOrderMark(false);
        file.close();   // �ر�file
        res = true;
    }
    else
        qDebug() << "file error!";
    m_mAuthList.unlock();
    return res;
}

bool st_client_file::addAuthUser(const USER_INFO_S &userInfo)
{
    if(userInfo.name.length() <= 0 || userInfo.password.length() <= 0)
        return false;
    bool res = false;
#ifdef USE_DATABASE
    USER_INFO_S tUserInfo = userInfo;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    GS_DB_BODY_C body;
    body = tUserInfo;
    res = m_dbTool->queryItem(db, TB_USERS_INFO_E, body);
    if(!res)
        res = m_dbTool->insertItem(db, TB_USERS_INFO_E, body);
#else
    QJsonDocument userDoc;
    if(openAuthUsers(userDoc))
    {
        QJsonObject usersObj = userDoc.object();
        if(!usersObj.contains(userInfo.name))
        {
            QJsonObject userObj;
            userObj["Name"] = userInfo.name;
            userObj["Password"] = userInfo.password;
            userObj["Auth"] = userInfo.auth;
            userObj["Date"] = userInfo.date;
            userObj["Message"] = userInfo.message;
            QJsonArray productArray;
            foreach (QString str, userInfo.products) {
                productArray << str;
            }
            userObj["Products"] = productArray;
            usersObj[userInfo.name] = userObj;
            userDoc.setObject(usersObj);
            if(saveAuthUsers(userDoc))
                res = true;
        }

    }
#endif
    return res;
}

bool st_client_file::removeAuthUser(const USER_INFO_S &userInfo)
{
    bool res = false;
#ifdef USE_DATABASE
    USER_INFO_S tUserInfo = userInfo;
    GS_DB_BODY_C body;
    body = userInfo;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->deleteItem(db, TB_USERS_INFO_E, body);
#else
    QJsonDocument userDoc;
    if(openAuthUsers(userDoc))
    {
        QJsonObject usersObj = userDoc.object();
        if(usersObj.contains(userInfo.name))
        {
            usersObj.remove(userInfo.name);
            userDoc.setObject(usersObj);
            if(saveAuthUsers(userDoc))
                res = true;
        }
        else
            res = true;
    }
#endif
    return res;
}

bool st_client_file::editAuthUser(const USER_INFO_S &userInfo)
{
    bool res = false;
#ifdef USE_DATABASE
    USER_INFO_S tUserInfo = userInfo;
    GS_DB_BODY_C body;
    body = tUserInfo;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    res = m_dbTool->updateItem(db, TB_USERS_INFO_E, body);
#else
    if(removeAuthUser(userInfo))
    {
        if(addAuthUser(userInfo))
            res = true;
    }
#endif
    return res;
}

bool st_client_file::loginClient(const BD_TMN_LOGIN_INFO_S loginInfo, USER_INFO_S &userInfo)
{
    bool auth = false;
#ifdef USE_DATABASE
    userInfo.name = QString(loginInfo.user_name);
    GS_DB_BODY_C body;
    body = userInfo;
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    bool res = m_dbTool->queryItem(db, TB_USERS_INFO_E, body);
    userInfo =  boost::any_cast<USER_INFO_S>(body);
    if(res)
    {
        if(userInfo.password == loginInfo.password)
        {
            auth = true;
            qDebug() << QString("User:%1,Auth:%2.login successful!").arg(userInfo.name).arg(userInfo.auth);
        }
        else
            qDebug() << QString("User:%1,Auth:%2.login failed!").arg(userInfo.name).arg(userInfo.auth);
    }
#else
    QJsonDocument userDoc;
    QString srcName(loginInfo.user_name);
    if(openAuthUsers(userDoc))
    {
        QJsonObject usersObj = userDoc.object();
        if(usersObj.contains(srcName))
        {
            QJsonObject userObj = usersObj[srcName].toObject();
            if(userObj.contains("Name") && userObj.contains("Password") && userObj.contains("Auth") && userObj.contains("Date")
                    && userObj.contains("Message") && userObj.contains("Products"))
            {
                QString srcPasswd(loginInfo.password);
                QString dstPasswd = userObj["Password"].toString();
                QString dstName = userObj["Name"].toString();
                if((srcPasswd == dstPasswd) && (srcName == dstName) && dstPasswd.length() > 0 && dstName.length() > 0)
                {
                    auth = true;
                    userInfo.name = srcName;
                    userInfo.password = srcPasswd;
                    userInfo.auth = userObj["Auth"].toInt();
                    userInfo.date = userObj["Date"].toString();
                    userInfo.message = userObj["Message"].toString();
                    userInfo.products.clear();
                    QJsonArray productArray = userObj["Products"].toArray();
                    foreach (QJsonValue val, productArray) {
                        userInfo.products << val.toString();
                    }
                    qDebug() << QString("User:%1,Auth:%2.login successful!").arg(userInfo.name).arg(userInfo.auth);
                }
            }
        }
    }
#endif
    return auth;
}

void st_client_file::setClientTable(ExampleServer::st_client_table *pClient)
{
    m_pClientTable = pClient;
}

void st_client_file::syncJson2Database()
{
#ifndef USE_DATABASE
    return;
#endif
    QScopedPointer<DatabaseTool> dbTool;
    dbTool.reset(new DatabaseTool);
    QScopedPointer<st_client_file> fileTool;
    fileTool.reset(new st_client_file);
    //ͬ���û���Ϣ
    QSqlDatabase db = m_pClientTable->dbRes()->databse(m_pClientTable->Database_UserAcct());
    bool dbExist = dbTool->tableExists(db, S_USERS_INFO_TABLE_NAME);
    if(!dbExist)
    {
        bool res = dbTool->createTable(db, TB_USERS_INFO_E);
        if(res)
        {
            QJsonDocument userDoc;
            if(fileTool->openAuthUsers(userDoc))
            {
                QJsonObject usersObj = userDoc.object();
                QJsonObject::const_iterator it = usersObj.begin();
                while(it != usersObj.end()){
                    QJsonObject userObj = it.value().toObject();
                    if(userObj.contains("Name") && userObj.contains("Password") && userObj.contains("Auth") && userObj.contains("Date")
                            && userObj.contains("Message") && userObj.contains("Products"))
                    {
                        USER_INFO_S userInfo;
                        userInfo.name = it.key();
                        userInfo.password = userObj["Password"].toString();
                        userInfo.auth = userObj["Auth"].toInt();
                        userInfo.date = userObj["Date"].toString();
                        userInfo.message = userObj["Message"].toString();
                        userInfo.products.clear();
                        QJsonArray productArray = userObj["Products"].toArray();
                        foreach (QJsonValue val, productArray) {
                            userInfo.products << val.toString();
                        }
                        GS_DB_BODY_C body;
                        body = userInfo;
                        dbTool->insertItem(db, TB_USERS_INFO_E, body);
                    }
                    it++;
                }
            }
        }
    }
    //return;
    //ͬ����Ʒ��Ϣ
    dbExist = dbTool->tableExists(db, S_PRODUCTS_INFO_TABLE_NAME);
    if(!dbExist)
    {
        dbTool->createTable(db, TB_GROUP_VERSION_INFO_E);
        dbTool->createTable(db, TB_MCU_VERSION_INFO_E);
        dbTool->createTable(db, TB_CRC_VERSION_INFO_E);
        bool res = dbTool->createTable(db, TB_PRODUCTS_INFO_E);
        if(res)
        {
            QString saveRootPath = "./version/";
            QString productFile = "ProductInfo.json";
            QDir dir("./version/");
            QStringList nameFilters;
            QStringList products = dir.entryList(nameFilters, QDir::Dirs, QDir::Name);
            QJsonDocument productDoc;
            foreach (QString productName, products) {
                if(productName == "." || productName == "..")
                    continue;
                QJsonDocument productDoc;
                QString fileName = saveRootPath + productName + "/" + productFile;
                if(!fileTool->openProductJson(fileName,productDoc))
                    continue;
                if(!productDoc.object().contains(productName))
                    continue;
                QJsonObject infoObj = productDoc.object()[productName].toObject();
                BODY_PRODUCT_INFO_S baseInfo;
                baseInfo.name = productName;
                baseInfo.desp = infoObj["ProductDesp"].toString();
                baseInfo.addDate = infoObj["Date"].toString();
                if(infoObj.contains("ModifyDate"))
                    baseInfo.modifyDate = infoObj["ModifyDate"].toString();
                baseInfo.savePath = infoObj["SaveFilePath"].toString();

                //CRC
                QJsonObject crcDftInfoObj = infoObj["CrcDefaultVersion"].toObject();
                QJsonArray crcInfoList = infoObj["CrcVersionList"].toArray();
                foreach (QJsonValue value, crcInfoList) {
                    QJsonObject infoObj = value.toObject();
                    BODY_CRC_VERSION_INFO_S info;
                    info.productName = productName;
                    info.name = infoObj["FileName"].toString();
                    info.date = infoObj["Date"].toString();
                    info.isDefaultVersion = infoObj["IsDefault"].toBool();
                    info.message = infoObj["Message"].toString();
                    info.fileName = infoObj["Name"].toString();
                    info.fileSize = infoObj["FileSize"].toString().toUInt();
                    info.custom = GetCustom(info.name);
                    if(infoObj.contains("Custom"))
                        info.custom = infoObj["Custom"].toString();
                    GS_DB_BODY_C body = info;
                    dbTool->insertItem(db, TB_CRC_VERSION_INFO_E, body);
                }

                //MCU
                QJsonArray mcuInfosArray = infoObj["McuInfos"].toArray();
                foreach (QJsonValue value, mcuInfosArray) {
                    QJsonObject mcuInfosObj = value.toObject();
                    QJsonObject mcuDftInfoObj = mcuInfosObj["McuDefaultVersion"].toObject();

                    QString mcuTypeName = mcuInfosObj["McuTypeName"].toString();
                    QJsonArray mcuInfoList = mcuInfosObj["McuVersionList"].toArray();
                    foreach (QJsonValue value, mcuInfoList) {
                        QJsonObject infoObj = value.toObject();
                        BODY_MCU_VERSION_INFO_S info;
                        info.productName = productName;
                        info.mcuTypeName = mcuTypeName;
                        info.name = infoObj["FileName"].toString();
                        info.date = infoObj["Date"].toString();
                        info.isDefaultVersion = infoObj["IsDefault"].toBool();
                        info.message = infoObj["Message"].toString();
                        info.fileName = infoObj["Name"].toString();
                        info.fileSize = infoObj["FileSize"].toString().toUInt();
                        GS_DB_BODY_C body = info;
                        dbTool->insertItem(db, TB_MCU_VERSION_INFO_E, body);
                    }
                }

                //GROUP
                QJsonArray groupInfosArray = infoObj["GroupFileInfos"].toArray();
                foreach (QJsonValue value, groupInfosArray) {
                    QJsonObject infoObj = value.toObject();
                    BODY_GROUP_VERSION_INFO_S info;
                    info.productName = productName;
                    info.name = infoObj["Name"].toString();
                    info.date = infoObj["Date"].toString();
                    info.isDefaultVersion = infoObj["IsDefault"].toBool();
                    info.message = infoObj["Message"].toString();
                    info.savePath = infoObj["SavePath"].toString();

                    QJsonArray fileInfoArray = infoObj["FileInfos"].toArray();
                    foreach (QJsonValue value, fileInfoArray) {
                        QJsonObject fileInfoObj = value.toObject();
                        info.subFileName = fileInfoObj["Name"].toString();
                        info.subFileDate = fileInfoObj["Date"].toString();
                        info.subFilePath = fileInfoObj["FileName"].toString();
                        info.subFileSize = fileInfoObj["FileSize"].toString().toUInt();
                        info.subFileMessage = fileInfoObj["Message"].toString();
                        GS_DB_BODY_C body = info;
                        dbTool->insertItem(db, TB_GROUP_VERSION_INFO_E, body);

                    }
                    if(fileInfoArray.isEmpty())
                    {
                        GS_DB_BODY_C body = info;
                        dbTool->insertItem(db, TB_GROUP_VERSION_INFO_E, body);
                    }
                }
                GS_DB_BODY_C body = baseInfo;
                dbTool->insertItem(db, TB_PRODUCTS_INFO_E, body);
            }
        }
        else
            qWarning() << "Create products info table failed!";

    }
}
}

