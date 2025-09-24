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
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"


/**
 * @brief       WK_UP �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void WKUP_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);               /* ���� */
    
    switch(GPIO_Pin)
    {
        case WKUP_INT_GPIO_PIN:
            if (WK_UP == 1)
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
            }
            break;
    }
}

/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    WKUP_GPIO_CLK_ENABLE();                                  /* WKUPʱ��ʹ�� */

    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;             /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);        /* WKUP����Ϊ�½��ش����ж� */

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 2, 2);               /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);                       /* ʹ���ж���0 */
}
