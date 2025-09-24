/**
 ****************************************************************************************************
 * @file        btim.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-04-20
 * @brief       ������ʱ�� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20220420
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/LED/led.h"
#include "./BSP/TIMER/btim.h"
#include "./SYSTEM/usart/usart.h"

TIM_HandleTypeDef g_timx_handle;         /* ��ʱ��������� */
TIM_HandleTypeDef g_tim7_handle;         /* ��ʱ��������� */

uint32_t FreeRTOSRunTimeTicks;
/* ʱ����ʱ���ĳ�ʼ�� */
void ConfigureTimeForRunTimeStats(void)
{
    btim_timx_int_init(10-1, 90-1);  /* 100����ϵͳʱ�ӽ��� */
    FreeRTOSRunTimeTicks = 0;
}

/**
 * @brief       ������ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ������ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ������ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ45M, ���Զ�ʱ��ʱ�� = 90Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr : �Զ���װֵ��
 * @param       psc : ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    g_timx_handle.Instance = BTIM_TIMX_INT;                      /* ��ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                          /* ��Ƶ */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;         /* ��������ģʽ */
    g_timx_handle.Init.Period = arr;                             /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_timx_handle);
    
    HAL_TIM_Base_Start_IT(&g_timx_handle);                       /* ʹ�ܶ�ʱ��x�Ͷ�ʱ�������ж� */
}

/* TIM7��ʼ������ */
void btim_tim7_int_init(uint16_t arr, uint16_t psc)
{
    g_tim7_handle.Instance = BTIM_TIM7_INT;                      /* ��ʱ��x */
    g_tim7_handle.Init.Prescaler = psc;                          /* ��Ƶ */
    g_tim7_handle.Init.CounterMode = TIM_COUNTERMODE_UP;         /* ��������ģʽ */
    g_tim7_handle.Init.Period = arr;                             /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_tim7_handle);
    
    HAL_TIM_Base_Start_IT(&g_tim7_handle);                       /* ʹ�ܶ�ʱ��x�Ͷ�ʱ�������ж� */
}
/**
 * @brief       ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
                �˺����ᱻHAL_TIM_Base_Init()��������
 * @param       ��
 * @retval      ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        BTIM_TIMX_INT_CLK_ENABLE();                     /* ʹ��TIMxʱ�� */
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 6, 0); /* ��ռ6�������ȼ�0 */
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);         /* ����ITMx�ж� */
    }
    if(htim->Instance == BTIM_TIM7_INT)
    {
        BTIM_TIM7_INT_CLK_ENABLE();                     /* ʹ��TIM7ʱ�� */
        HAL_NVIC_SetPriority(BTIM_TIM7_INT_IRQn, 4, 0); /* ��ռ4�������ȼ�0 */
        HAL_NVIC_EnableIRQ(BTIM_TIM7_INT_IRQn);         /* ����ITM7�ж� */
    }
}

/**
 * @brief       ������ʱ��TIMX�жϷ�����
 * @param       ��
 * @retval      ��
 */
void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);  /* ��ʱ���ص����� */
}

/* TIM7�жϷ����� */
void BTIM_TIM7_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_tim7_handle);  /* ��ʱ���ص����� */
}

/**
 * @brief       �ص���������ʱ���жϷ���������
 * @param       ��
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        FreeRTOSRunTimeTicks++;
    }else if(htim->Instance == BTIM_TIM7_INT)
    {
        printf("TIM7���ȼ�Ϊ4���������У���������\r\n");
    }
}
