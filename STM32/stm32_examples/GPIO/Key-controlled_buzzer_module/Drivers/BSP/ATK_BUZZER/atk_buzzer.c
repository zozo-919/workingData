/**
 ****************************************************************************************************
 * @file        atk_buzzer.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2024-11-01
 * @brief       ������ ��������
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

#include "./BSP/ATK_BUZZER/atk_buzzer.h"


/**
 * @brief       ������ģ���ʼ������
 * @param       ��
 * @retval      ��
 */
void atk_buzzer_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    ATK_BUZZER_GPIO_CLK_ENABLE();                               /* ʱ��ʹ�� */

    gpio_init_struct.Pin = ATK_BUZZER_GPIO_PIN;                 /* ATK_BUZZER���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                /* ������� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(ATK_BUZZER_GPIO_PORT, &gpio_init_struct);     /* ���ų�ʼ�� */

    ATK_BUZZER(0);                                              /* �ر� ������ */
}


