/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    DMA����չʾʵ�飨����DMA��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� M48Z-M3��Сϵͳ��STM32F103��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/KEY/key.h"


const uint8_t text_to_send[] = {"����ԭ�� M48Z-M3��Сϵͳ��STM32F103�� DMA����\r\n"};           /* Ҫѭ�����͵��ַ��� */
#define SEND_BUF_SIZE (sizeof(text_to_send) * 300)                                              /* �������ݳ��� */
uint8_t g_sendbuf[SEND_BUF_SIZE];       

int main(void)
{
    uint16_t len;
    uint16_t i;
    uint8_t key;
    uint8_t cpu_state = 0;
    
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */
    led_init();                                             /* ��ʼ��LED */
    key_init();                                             /* ��ʼ��KEY */

    len = sizeof(text_to_send);                             /* ��䷢�����ݻ����� */
    
    for (i = 0; i < SEND_BUF_SIZE; i++)
    {
        g_sendbuf[i] = text_to_send[i % len];
    }
    
    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)       /* KEY0���� */
        {
            /* ���������һֱռ��CPU��ʹ��Ȩ�����봫���������֮��Ż��ͷ� */
            HAL_UART_Transmit(&g_uart1_handle, g_sendbuf, SEND_BUF_SIZE, HAL_MAX_DELAY);
            cpu_state = 1;
        }
        
        /* ��CPU��ʹ��Ȩ���ͷţ����������� */
        if(cpu_state == 1)
        {
            LED0(0);
            cpu_state = 0;
        }

        delay_ms(10);
    }
}
