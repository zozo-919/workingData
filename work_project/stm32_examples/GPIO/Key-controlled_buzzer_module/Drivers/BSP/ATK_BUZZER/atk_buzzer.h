/**
 ****************************************************************************************************
 * @file        atk_buzzer.h
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


#ifndef __ATK_BUZZER_H
#define __ATK_BUZZER_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

#define ATK_BUZZER_GPIO_PORT                  GPIOA
#define ATK_BUZZER_GPIO_PIN                   GPIO_PIN_3
#define ATK_BUZZER_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)          

/******************************************************************************************/
/* BUZZER���� �궨�� */
#define ATK_BUZZER(x)   do{ x ? \
                            HAL_GPIO_WritePin(ATK_BUZZER_GPIO_PORT, ATK_BUZZER_GPIO_PIN, GPIO_PIN_SET) : \
                            HAL_GPIO_WritePin(ATK_BUZZER_GPIO_PORT, ATK_BUZZER_GPIO_PIN, GPIO_PIN_RESET); \
                        }while(0)          

/* BUZZERȡ�� �궨�� */
#define ATK_BUZZER_TOGGLE()   do{ HAL_GPIO_TogglePin(ATK_BUZZER_GPIO_PORT, ATK_BUZZER_GPIO_PIN); }while(0)  

/******************************************************************************************/
/* �ⲿ�ӿں���*/
void atk_buzzer_init(void);                 /* ��ʼ�� */
#endif
