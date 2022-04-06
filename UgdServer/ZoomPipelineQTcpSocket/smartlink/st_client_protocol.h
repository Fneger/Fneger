#ifndef ST_CLIENT_PROTOCOL_H
#define ST_CLIENT_PROTOCOL_H


#include <qglobal.h>
#include <QString>
#include "st_message.h"
#include "st_packet_tool.h"
namespace BdUgdServer {
    //Զ�̰汾����ͨѶЭ����غ���
    class st_client_protocol:public st_packet_tool
    {
    public:
        explicit st_client_protocol();
    protected:
        uint16_t packing(uint16_t type, void *pPacket,uint8_t res = 0);

    protected:
        QString m_deviceIdStr;
        QByteArray m_txBuf; //GPRS���ݷ��ͻ���
        uint8_t m_MsgProperties;    //��Ϣ����
        uint16_t m_DownlinkMSN; //���������͵��ն�����Message serial number
        uint16_t m_UplinkMSN;   //�ն˷��͵�����������Message serial number
        uint8_t m_DeviceID[8];  //�豸ID,m_DeviceID[7]ΪxorУ��λ
        uint16_t m_DownlinkFID; //���������͵��ն˵�Message function ID ����
        uint16_t m_UplinkFID;   //�ն˷��͵���������Message function ID ����

    };
}


#endif // ST_CLIENT_PROTOCOL_H
