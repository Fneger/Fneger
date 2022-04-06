#ifndef CASIODATABASE_H
#define CASIODATABASE_H

#include "boost/noncopyable.hpp"
#include "ioserviceclass.h"
#include "st_global_def.h"
#include <protobuf_message.pb.h>
#include <boost/function.hpp>


using namespace GsGlobalDef;
struct QUERY_DB_PARAMS;
typedef boost::function<void (QUERY_DB_PARAMS &)> DbQueryCb;

typedef struct QUERY_DB_PARAMS{
    QSqlDatabase db;
    fneger::QueryCode queryCode;
    GS_BODY_TYPE nType;
    GS_DB_BODY_C queryBody; //查询所需信息
    GS_DB_BODY_C dbBody; //储存单个结构体
    GS_DB_BODY_C dbBodys; //储存多个结构体
    QString extTableName;
    int startId = 0;
    int nItemCntMax = S_QUERY_ITEM_NUM_MAX;
    bool result = false;
    QString tips;
    DbQueryCb callback;
} QUERY_DB_PARAMS_S;

typedef struct QUERY_DEFAULT_VERSION{
    QString productName;
    QString fileType;
    QString fileSubType;
    QString custom;
}QUERY_DEFAULT_VERSION_S;

namespace ExampleServer {
class st_client_table;
}

using namespace fneger;
class CAsioDatabase : public boost::noncopyable
{
public:
    static CAsioDatabase *Instance();

    template<typename F, typename...Args>
    void addDbQuery(F &&f, Args&&...args)
    {
        io_svr_->post(f,args...);
    }

    //根据条件查询数据表某一项
    static void queryItem(QUERY_DB_PARAMS_S &params);
    //获取表中多个元素,其中保存结构体指针内存需在使用后释放
    static void queryItems(QUERY_DB_PARAMS_S &params);
    //多表联合查询
    static void joinQueryItems(QUERY_DB_PARAMS_S params);

    static ExampleServer::st_client_table * s_client_table_;
private:
    CAsioDatabase();
    virtual ~CAsioDatabase();
    static void putDb2Struct(GS_BODY_TYPE nType, GS_DB_BODY_C &body, const QSqlQuery &query);
    static void putDb2Struct(QueryCode nCode, GS_DB_BODY_C &body, const QSqlQuery &query);
    boost::shared_ptr<IOServiceClass> io_svr_;
    static CAsioDatabase *S_pThis;

};

#endif // CASIODATABASE_H
