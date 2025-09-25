#include "./BSP/ATK_24C02/atk_24c02.h"
#include "./BSP/IIC/myiic.h"
#include "./SYSTEM/delay/delay.h"


void atk_24c02_init(void)
{
    iic_init();
}

void atk_24cxx_write_one_byte(uint16_t addr,  uint8_t data)
{
    iic_start();            /* 发送起始信号 */
    iic_send_byte(0XA0);    /* 发送器件 0XA0 */
    iic_wait_ack(); 
    iic_send_byte(addr);    /* 发送地址 */
    iic_wait_ack(); 
    iic_send_byte(data);    /* 发送1字节 */
    iic_wait_ack(); 
    iic_stop();             /* 产生一个停止条件 */
    delay_ms(10);           /* EEPROM 写入比较慢 */      
}

uint8_t  atk_24cxx_read_one_byte(uint16_t  addr)
{
    uint8_t temp = 0;
    iic_start();                    /* 发送起始信号 */
    iic_send_byte(0XA0);            /* 发送器件 0XA0 */
    iic_wait_ack();                 /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr);            /* 发送低位地址 */
    iic_wait_ack();                 /* 等待ACK, 此时地址发送完成了 */
    iic_start();                    /* 重新发送起始信号 */ 
    iic_send_byte(0XA1);            /* 进入接收模式, IIC规定最低位是0, 表示读取 */
    iic_wait_ack();                 /* 每次发送完一个字节,都要等待ACK */
    temp = iic_read_byte(0);        /* 接收一个字节数据 */
    iic_stop();                     /* 产生一个停止条件 */
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

