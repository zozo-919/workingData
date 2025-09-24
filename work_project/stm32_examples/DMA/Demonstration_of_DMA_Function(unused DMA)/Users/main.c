/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    DMA作用展示实验（启用DMA）
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 M48Z-M3最小系统板STM32F103版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/KEY/key.h"


const uint8_t text_to_send[] = {"正点原子 M48Z-M3最小系统板STM32F103版 DMA测试\r\n"};           /* 要循环发送的字符串 */
#define SEND_BUF_SIZE (sizeof(text_to_send) * 300)                                              /* 发送数据长度 */
uint8_t g_sendbuf[SEND_BUF_SIZE];       

int main(void)
{
    uint16_t len;
    uint16_t i;
    uint8_t key;
    uint8_t cpu_state = 0;
    
    HAL_Init();                                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
    delay_init(72);                                         /* 延时初始化 */
    usart_init(115200);                                     /* 初始化串口 */
    led_init();                                             /* 初始化LED */
    key_init();                                             /* 初始化KEY */

    len = sizeof(text_to_send);                             /* 填充发送数据缓冲区 */
    
    for (i = 0; i < SEND_BUF_SIZE; i++)
    {
        g_sendbuf[i] = text_to_send[i % len];
    }
    
    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)       /* KEY0按下 */
        {
            /* 这个函数会一直占用CPU的使用权，必须传输完成数据之后才会释放 */
            HAL_UART_Transmit(&g_uart1_handle, g_sendbuf, SEND_BUF_SIZE, HAL_MAX_DELAY);
            cpu_state = 1;
        }
        
        /* 当CPU的使用权被释放，进来这里点灯 */
        if(cpu_state == 1)
        {
            LED0(0);
            cpu_state = 0;
        }

        delay_ms(10);
    }
}
