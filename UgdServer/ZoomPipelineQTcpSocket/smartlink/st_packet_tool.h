#ifndef PACKET_TOOL_H
#define PACKET_TOOL_H

#include <qglobal.h>
namespace BdUgdServer {
class st_packet_tool{
public:
    st_packet_tool(){}
    //BCD��ת�ַ���
    bool bcd2str(char *str,uint8_t *bcd,int len);
    //�ַ���תBCD��
    bool str2bcd(uint8_t *bcd, char *str, int *bcd_len);
    //��ȡ֡���ֵ
    uint8_t frame_xor(uint8_t *ptr,uint16_t len);
    //����֡ת��,����ת���֡���� 0xE7->0xE6+0x02,0xE6->0xE6+0x01
    uint16_t frame_escape(uint8_t *ptr,uint16_t len);
    //����֡��ת��,���ط�ת���֡���� 0xE6+0x02->0xE7,0xE6+0x01->0xE6
    uint16_t frame_reverse_escape(uint8_t *ptr,uint16_t len);
    //�ж�����֡�Ƿ�Ϸ�
    bool frame_check(uint8_t *ptr,uint16_t len);
    //���������������
    uint16_t send_data(uint8_t *ptr, uint16_t len);
    //��ӡ����
    void print_data(uint8_t *ptr,uint16_t len);
    //���2Bytes
    inline void put2bytes(uint8_t *dst, uint16_t src, uint16_t *pos);
    //���4Bytes
    inline void put4bytes(uint8_t *dst,uint32_t src, uint16_t *pos);
    //���8Bytes
    inline void put8bytes(uint8_t *dst,uint64_t src, uint16_t *pos);
    //���uint16_t
    inline uint16_t get2bytes(uint8_t *dst,uint16_t *pos);
    //���uint32_t
    inline uint32_t get4bytes(uint8_t *dst,uint16_t *pos);
    //���uint64_t
    inline uint64_t get8bytes(uint8_t *dst,uint16_t *pos);
};

//���2Bytes
void st_packet_tool::put2bytes(uint8_t *dst,uint16_t src,uint16_t *pos)
{
    dst[0] = 0xFF & (src >> 8);
    dst[1] = 0xFF & src;
    *pos += 2;
}

//���4Bytes
void st_packet_tool::put4bytes(uint8_t *dst,uint32_t src,uint16_t *pos)
{
    dst[0] = 0xFF & (src >> 24);
    dst[1] = 0xFF & (src >> 16);
    dst[2] = 0xFF & (src >> 8);
    dst[3] = 0xFF & src;
    *pos += 4;
}

//���8Bytes
void st_packet_tool::put8bytes(uint8_t *dst, uint64_t src, uint16_t *pos)
{
    dst[0] = 0xFF & (src >> 56);
    dst[1] = 0xFF & (src >> 48);
    dst[2] = 0xFF & (src >> 40);
    dst[3] = 0xFF & (src >> 32);
    dst[4] = 0xFF & (src >> 24);
    dst[5] = 0xFF & (src >> 16);
    dst[6] = 0xFF & (src >> 8);
    dst[7] = 0xFF & src;
    *pos += 8;
}

uint16_t st_packet_tool::get2bytes(uint8_t *dst,uint16_t *pos)
{
    uint16_t v = 0;
    v = ((uint16_t)dst[0] << 8 )| dst[1];
    *pos += 2;
    return v;
}

uint32_t st_packet_tool::get4bytes(uint8_t *dst,uint16_t *pos)
{
    uint32_t v = 0;
    v = ((uint32_t)dst[0] << 24 ) | (uint32_t)(dst[1] << 16 ) | ((uint32_t)dst[2] << 8 )| (uint32_t)dst[3];
    *pos += 4;
    return v;
}

uint64_t st_packet_tool::get8bytes(uint8_t *dst,uint16_t *pos)
{
    uint64_t v = 0;
    v = ((uint64_t)dst[0] << 56 ) | ((uint64_t)dst[1] << 48 ) | ((uint64_t)dst[2] << 40 ) | ((uint64_t)dst[3] << 32 )
            | ((uint64_t)dst[4] << 24 ) | ((uint64_t)dst[5] << 16 ) | ((uint64_t)dst[6] << 8 )| dst[7];
    *pos += 8;
    return v;
}

}

#endif // PACKET_TOOL_H
