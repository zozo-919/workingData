/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2024-11-01
 * @brief    ADC作用展示 实验
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
#include "./BSP/ADC/adc.h"



int main(void)
{
    uint16_t adcdata;
    uint16_t voltage;
    
    HAL_Init();                                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
    delay_init(72);                                         /* 延时初始化 */
    usart_init(115200);                                     /* 初始化串口 */
    led_init();                                             /* 初始化LED */
    adc_init();                                             /* 初始化ADC */
    
    while (1)
    {
        adcdata = adc_get_result_average(ADC_ADCX_CHY, 10); /* 获取ADC通道5转换且进行均值滤波后的结果 */

        voltage = (adcdata * 3300) / 4095;                  /* 计算实际电压值（扩大1000倍） */
        printf("电压值:%d.%dV\r\n",voltage / 1000,voltage % 1000);
        
        LED0_TOGGLE();
        delay_ms(1000);
    }
}
