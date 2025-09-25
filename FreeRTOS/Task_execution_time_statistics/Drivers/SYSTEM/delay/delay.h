#ifndef __DELAY_H
#define __DELAY_H

#include "./SYSTEM/sys/sys.h"


void delay_init(uint16_t sysclk);           /* ��ʼ���ӳٺ��� */
void delay_ms(uint16_t nms);                /* ��ʱnms */
void delay_us(uint32_t nus);                /* ��ʱnus */

#if (!SYS_SUPPORT_OS)                       /* û��ʹ��Systick�ж� */
    void HAL_Delay(uint32_t Delay);         /* HAL�����ʱ������SDIO����Ҫ�õ� */
#endif

#endif

