/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       �������ͻָ� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"
#include "./BSP/TIMER/btim.h"

int main(void)
{
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(360, 25, 2, 8);        /* ����ʱ��,180Mhz */
    delay_init(180);                            /* ��ʱ��ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                                 /* ��ʼ��LED */
    key_init();                                 /* ��ʼ������ */
    sdram_init();                               /* SRAM��ʼ�� */
    lcd_init();                                 /* ��ʼ��LCD */
    btim_timx_int_init(10000 - 1 ,9000 - 1);    /* 1s�ж�һ�� */
    btim_tim7_int_init(10000 - 1 ,9000 - 1);    /* 1s�ж�һ�� */
    
    my_mem_init(SRAMIN);                        /* ��ʼ���ڲ��ڴ�� */
    my_mem_init(SRAMEX);                        /* ��ʼ���ⲿ�ڴ�� */
    my_mem_init(SRAMCCM);                       /* ��ʼ��CCM�ڴ�� */
    
    freertos_demo();
}
