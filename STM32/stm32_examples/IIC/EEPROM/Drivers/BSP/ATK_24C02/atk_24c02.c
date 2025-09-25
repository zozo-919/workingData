#include "./BSP/ATK_24C02/atk_24c02.h"
#include "./BSP/IIC/myiic.h"
#include "./SYSTEM/delay/delay.h"


void atk_24c02_init(void)
{
    iic_init();
}

void atk_24cxx_write_one_byte(uint16_t addr,  uint8_t data)
{
    iic_start();            /* ������ʼ�ź� */
    iic_send_byte(0XA0);    /* �������� 0XA0 */
    iic_wait_ack(); 
    iic_send_byte(addr);    /* ���͵�ַ */
    iic_wait_ack(); 
    iic_send_byte(data);    /* ����1�ֽ� */
    iic_wait_ack(); 
    iic_stop();             /* ����һ��ֹͣ���� */
    delay_ms(10);           /* EEPROM д��Ƚ��� */      
}

uint8_t  atk_24cxx_read_one_byte(uint16_t  addr)
{
    uint8_t temp = 0;
    iic_start();                    /* ������ʼ�ź� */
    iic_send_byte(0XA0);            /* �������� 0XA0 */
    iic_wait_ack();                 /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr);            /* ���͵�λ��ַ */
    iic_wait_ack();                 /* �ȴ�ACK, ��ʱ��ַ��������� */
    iic_start();                    /* ���·�����ʼ�ź� */ 
    iic_send_byte(0XA1);            /* �������ģʽ, IIC�涨���λ��0, ��ʾ��ȡ */
    iic_wait_ack();                 /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    temp = iic_read_byte(0);        /* ����һ���ֽ����� */
    iic_stop();                     /* ����һ��ֹͣ���� */
    return temp;
}


void atk_24cxx_write(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while(datalen--)
    {
        atk_24cxx_write_one_byte(addr++,  *pbuf++);
    }
}
void atk_24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while(datalen--)
    {
        *pbuf++ = atk_24cxx_read_one_byte(addr++);
    }
}

