#ifndef CBDUGDCLIENTPROTOCOL_H
#define CBDUGDCLIENTPROTOCOL_H

#include <qglobal.h>
#include <QString>
#include "st_message.h"
#include "st_packet_tool.h"

using namespace BdUgdServer;
class CBdUgdClientProtocol:public st_packet_tool
{
public:
    CBdUgdClientProtocol();
    ~CBdUgdClientProtocol(){}
    //���ݷ��
    uint16_t Packing(BD_PACKET_FUNC_ID_E type, void *pPacket,uint8_t res = 0);
    // ����bufptr, ���ؽ����ĳ���.
    // �������һ����Ч��bb��, ������麯������.
    int ParsePacket(uint8_t *bufptr, uint16_t buflen);
    virtual void SendPacket(BD_PACKET_FUNC_ID_E fid,void *data,uint8_t res = 0) = 0;
    //�������ݰ����ڷ���
    uint16_t BuildPacket(uint8_t *txdata, BD_PACKET_FUNC_ID_E type, void *pPacket, uint8_t res);
    //����Tcp��������������
    void SendHeartbeatPacket();
    //������Ч���ݰ�
    virtual int OnParseValidPacket(quint8 *extdata, int extdatalen) = 0;
    //��ȡϵͳʱ��
    static time_t GetSysTime(uint8_t *datetime,uint8_t len);
    //��ȡʱ��
    static void GetTime(time_t nowTime,uint8_t *datetime,uint8_t len);

   //��ȡ�豸ID�ַ���
   inline QString GetDeviceId() const { return m_deviceId; }
   //�����豸ID 7Bytes BCD
   void SetDeviceId(char *id);

private:


protected:
    uint16_t m_downlinkFID; //���������͵��ն˵�Message function ID ����
    uint16_t m_uplinkFID;   //�ն˷��͵���������Message function ID ����
    uint16_t m_downUplinkFID; //Ӧ����Ϣ���������ݹ���ID
    uint16_t m_downlinkMSN; //���������͵��ն�����Message serial number
    uint16_t m_uplinkMSN;   //�ն˷��͵�����������Message serial number

private:
    uint8_t m_deviceID[8];  //�豸ID,m_DeviceID[7]ΪxorУ��λ
    uint8_t m_gprsDataRX[DATA_PAYLOAD]; //GPRS���ݽ��ջ���
    uint8_t m_gprsDataTX[DATA_PAYLOAD]; //GPRS���ݷ��ͻ���
    uint16_t m_msgProperties;    //��Ϣ����
    QString m_deviceId;
};

#endif // CBDUGDCLIENTPROTOCOL_H
