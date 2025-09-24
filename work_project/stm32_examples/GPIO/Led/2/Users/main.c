/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    �½�����ʵ��-HAL��汾ʵ��
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


int main(void)
{
    GPIO_InitTypeDef  gpio_init_struct;
    
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */

    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    
    __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_AFIO_CLK_ENABLE();        /* ����AFIO�Ĵ�������Ҫʹ��AFIOʱ�� */
    __HAL_AFIO_REMAP_SWJ_NOJTAG();      /* ʹ��SWD���ط�ʽ����ʹ�øú궨������ͷ�PA15��PB3��PB4��3��IO�ڣ������� */
//    __HAL_AFIO_REMAP_SWJ_DISABLE();   /* �ú궨����ͷ�PA13��PA14��PA15��PB3��PB4��5��IO�ڣ�������һ�����ر�ͨ��ʧ�ܴ��󣬲������� */
    
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);
    

    while(1)
    { 
        /* �������� */
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
        delay_ms(200);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        delay_ms(200);
    }
}
