/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2024-11-01
 * @brief    ADC����չʾ ʵ��
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
#include "./BSP/ADC/adc.h"



int main(void)
{
    uint16_t adcdata;
    uint16_t voltage;
    
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */
    led_init();                                             /* ��ʼ��LED */
    adc_init();                                             /* ��ʼ��ADC */
    
    while (1)
    {
        adcdata = adc_get_result_average(ADC_ADCX_CHY, 10); /* ��ȡADCͨ��5ת���ҽ��о�ֵ�˲���Ľ�� */

        voltage = (adcdata * 3300) / 4095;                  /* ����ʵ�ʵ�ѹֵ������1000���� */
        printf("��ѹֵ:%d.%dV\r\n",voltage / 1000,voltage % 1000);
        
        LED0_TOGGLE();
        delay_ms(1000);
    }
}
