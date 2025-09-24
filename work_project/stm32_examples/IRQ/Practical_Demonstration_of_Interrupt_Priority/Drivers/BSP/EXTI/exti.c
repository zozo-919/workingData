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
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    /* ѭ��ģ��DO���ⲿ�жϼ���ʼ�� */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_init_struct.Pin = GPIO_PIN_3;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;   /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;            /* ����������ⲿ�������ȶ������� */
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 2);         /* ��ռ1�������ȼ�2 */
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);                 /* ʹ���ж���1 */
    
    
    /* PB7�����ⲿ�жϼ���ʼ�� */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    gpio_init_struct.Pin = GPIO_PIN_7;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;    /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;          /* ���� */
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 2);       /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);               /* ʹ���ж���1 */
}

/**
 * @brief       EXTI3�ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);   /* �����жϴ����ú��� ���EXTI3 ���жϱ�־λ */
}

/**
 * @brief       EXTI9_5�ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);   /* �����жϴ����ú��� ���EXTI7 ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);   /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);    /* �˳��ж�ǰϨ��LED�� */
}

/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_3)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
    }
    
    delay_ms(10);      /* ���� */
    
    if (GPIO_Pin == GPIO_PIN_7)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);    /* ����LED�� */
        delay_ms(5000);      /* ��5�룬ʵ��Ӧ�þ�����Ҫ���жϳ���ʹ����ʱ�������˴�Ϊ����ʾ */
    }
}

