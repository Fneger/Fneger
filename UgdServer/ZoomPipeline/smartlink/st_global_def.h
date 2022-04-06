#ifndef ST_GLOBAL_DEF_H
#define ST_GLOBAL_DEF_H

#include <boost/any.hpp>

#include <QtCore>
#include <QSqlDatabase>


namespace GsGlobalDef {
typedef boost::any GS_DB_BODY_C;

//���ݿ����Ϣ
typedef enum{
    TB_USERS_INFO_E, //�û���Ϣ
    TB_PRODUCTS_INFO_E, //��Ʒ��Ϣ
    TB_CRC_VERSION_INFO_E,  //Crc�汾��Ϣ
    TB_MCU_VERSION_INFO_E,  //Mcu�汾��Ϣ
    TB_GROUP_VERSION_INFO_E,    //����ļ���Ϣ
    TB_LOG_INFO_E,  //��־��Ϣ
    TB_TMN_INFO_LOG_INFO_E,  //�ն˵�¼��Ϣ��־
    TB_TYPE_MAX,
}GS_BODY_TYPE;

//��־����
typedef enum{
    LOG_UPGRADE_E,  //��Ʒ������־
    LOG_DEV_MODULE_E,   //�豸ģ��״̬
    LOG_TYPE_MAX    //������־����
}GS_LOG_TYPE;

//��������
typedef enum{
    UPGRADE_CRC_E,  //CRC
    UPGRADE_MCU_E,  //MCU
    UPGRADE_GROUP_E,    //GROUP
    UPGRADE_TYPE_MAX
} GS_UPGRADE_TYPE;

//�豸ģ������
typedef enum{
    DEV_MODULE_4G_E,   //4Gģ��
    DEV_MODULE_GPS_E,  //GPS
    DEV_MODULE_DISK_E, //����
    DEV_MODULE_PWR_E,  //��Դ
    DEV_MODULE_TYPE_MAX
} GS_DEV_MODULE_TYPE;

//��ӡ��־ʱ��Ӧ����ִ�н��
typedef enum{
    LOG_RESULT_SUCC_E,  //�ɹ�
    LOG_RESULT_IN_EXEC_E,   //ִ����
    LOG_RESULT_FAILED_E,    //ʧ��
    LOG_RESULT_MAX,     //���з��ؽ��
}GS_LOG_RESULT;

//�豸ģ��״̬
typedef enum{
    DEV_MODULE_NORMAL_E,    //����
    DEV_MODULE_ABNORMAL_E,  //һ��
    DEV_MODULE_STATUS_MAX
}GS_DEV_MODULE_STATUS;

//��Ʒ��Ϣ
typedef struct {
    int id;
    QString name; //��Ʒ����
    QString desp;   //������Ϣ
    QString addDate;   //�������
    QString modifyDate; //�޸�����
    QString savePath;  //�ļ�����·��
} BODY_PRODUCT_INFO_S;

//Crc�汾��Ϣ
typedef struct {
    BODY_PRODUCT_INFO_S productInfo;
    int id;
    QString productName; //��Ʒ����
    QString name;   //�汾����
    QString date;   //�������
    bool isDefaultVersion; //�Ƿ�Ĭ�ϰ汾
    QString message;    //�汾˵��
    QString fileName;   //�ļ�����ȫ·��
    uint32_t fileSize;  //�ļ���С
    QString custom;     //������Ϣ BD��BD_C1��BD_C2
}BODY_CRC_VERSION_INFO_S;

//Mcu�汾��Ϣ
typedef struct {
    BODY_PRODUCT_INFO_S productInfo;
    int id;
    QString productName; //��Ʒ����
    QString mcuTypeName;    //mcu��������
    QString name;   //�汾����
    QString date;   //�������
    bool isDefaultVersion; //�Ƿ�Ĭ�ϰ汾
    QString message;    //�汾˵��
    QString fileName;   //�ļ�����ȫ·��
    uint32_t fileSize;  //�ļ���С
}BODY_MCU_VERSION_INFO_S;

//Group�汾��Ϣ
typedef struct {
    BODY_PRODUCT_INFO_S productInfo;
    int id;
    QString productName; //��Ʒ����
    QString name;   //����ļ�����
    QString date;   //�������
    bool isDefaultVersion; //�Ƿ�Ĭ�ϰ汾
    QString message;    //�汾˵��
    QString savePath;   //����ļ�����·��
    QString subFileName;    //����ļ����ļ�����
    QString subFileDate; //����ļ����ļ��������
    QString subFilePath;   //����ļ����ļ�����ȫ·��
    uint32_t subFileSize;    //����ļ����ļ���С
    QString subFileMessage; //���ļ���ע��Ϣ
}BODY_GROUP_VERSION_INFO_S;

//��־��Ϣ
typedef struct {
    int id;
    QString productName; ////��Ʒ����
    QString devNumber;  //�豸��
    QString imeiNumber; //4Gģ�� IMEI
    QString fwVersion;    //�̼��汾
    GS_LOG_TYPE type;   //��־����
    int subtype;   //��־������
    GS_LOG_RESULT result; //ִ�н��
    QDateTime dateTime;   //��־����ʱ��
    QDateTime serverDateTime;   //����������ʱ��
    QString message;    //��־����
} BODY_LOG_INFO_S;

//��־������
typedef struct {
    QString tableName;   //���ݱ�����
    bool isCreated;     //�Ƿ��Ѵ���
    int startDevNumber; //��ʼ�豸��
    int endDevNumber;   //�����豸��
    bool isFull;    //�Ƿ�����
    int savedItemNum; //�ѱ�������
}LOG_TABLE_MAN_S;

//��������ַ��Ϣ
typedef struct{
    QString ipAddr;
    int port;
} BODY_SERVER_INFO_S;


//�����ն���Ϣ
typedef struct{
    int id;
    QString productName;   //��Ʒ����
    QString deviceNum;		/*����(��Χ:000000~999999*/
    QString phoneNumber;   /*�ֻ���*/
    QString licenseNum;    /*���ƺ���*/
    QString videoId;       /*��ƵID*/
    QString terminalId;    //�ն�ID
    QString imeiNumber; //4Gģ�� IMEI
    QString crcVersion;    //crc�汾��
    QString mcuVersion;    //mcu�汾��
    int authorizationStatus; //��Ȩ״̬��0��δ��Ȩ��1������Ȩ��2����Ȩʧ��
    QList<BODY_SERVER_INFO_S> serverInfos; //����ƽ̨��Ϣ
    QDateTime dateTime;   //��־����ʱ��
    QDateTime serverDateTime;   //����������ʱ��
}BODY_TMN_INFO_S;


extern const QString S_USERS_INFO_TABLE_NAME;
extern const QString S_PRODUCTS_INFO_TABLE_NAME;
extern const QString S_CRC_VERSION_INFO_TABLE_NAME;
extern const QString S_MCU_VERSION_INFO_TABLE_NAME;
extern const QString S_GROUP_VERSION_INFO_TABLE_NAME;
extern const QString S_LOG_INFO_TABLE_NAME;
extern const QString S_TMN_INFO_LOG_INFO_TABLE_NAME;
extern const int S_QUERY_ITEM_NUM_MAX;
extern const int S_LOG_TABLE_DEV_MAX;
extern const int S_LOG_TABLE_ITEM_MAX;
extern const int S_LOG_TABLE_DEV_ID_MAX;

}



class st_global_def
{
public:
    st_global_def();
};

#endif // ST_GLOBAL_DEF_H
