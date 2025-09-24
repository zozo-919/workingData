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
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"


int main(void)
{
    uint8_t key;
    
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */
    led_init();
    key_init();
    
    while(1)
    {
        key = key_scan(0);              /* �õ���ֵ */

        if (key)
        {
            switch (key)
            {
                case KEY0_PRES:
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
                    break;
                
                case KEY1_PRES:
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
                    break;

                case KEY2_PRES:
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
                    break;

                case KEY3_PRES:
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
                    break;
            }
        }
    }
}
