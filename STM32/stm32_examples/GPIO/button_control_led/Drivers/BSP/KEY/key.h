 /**
 ****************************************************************************************************
 * @file        key.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       �������� ��������
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

#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"


#define KEY0        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)     /* ��ȡKEY0���� */
#define KEY1        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)     /* ��ȡKEY1���� */
#define KEY2        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)     /* ��ȡKEY2���� */
#define KEY3        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)     /* ��ȡKEY3���� */


#define KEY0_PRES    1              /* KEY0���� */
#define KEY1_PRES    2              /* KEY1���� */
#define KEY2_PRES    3              /* KEY2���� */
#define KEY3_PRES    4              /* KEY3���� */



void key_init(void);                /* ������ʼ������ */
uint8_t key_scan(uint8_t mode);     /* ����ɨ�躯�� */

#endif


















