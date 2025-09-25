/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       �ⲿ�ж� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� M48Z-M3��Сϵͳ��STM32F103��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./BSP/LED/led.h"
#include "./BSP/EXTI/exti.h"



/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_init_struct.Pin = GPIO_PIN_3;
    gpio_init_struct.Mode  = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    
    HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

///* EXTI3�ⲿ�жϷ����� */
//void EXTI3_IRQHandler(void)
//{
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != 0)
//    {
//        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
//    }
//}

/* EXTI3�ⲿ�жϷ����� */
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

/* �ⲿ�жϻص����� */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_3)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
    }
}
