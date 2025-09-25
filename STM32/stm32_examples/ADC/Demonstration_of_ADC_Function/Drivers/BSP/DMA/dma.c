/**
 ****************************************************************************************************
 * @file        dma.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       DMA ��������
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

#include "./BSP/DMA/dma.h"
#include "./SYSTEM/delay/delay.h"


DMA_HandleTypeDef  g_dma_handle;            /* DMA��� */
extern UART_HandleTypeDef g_uart1_handle;   /* UART��� */


/**
 * @brief       ����TX DMA��ʼ������
 *   @note      ����Ĵ�����ʽ�ǹ̶���, ���Ҫ���ݲ�ͬ��������޸�
 *              �Ӵ洢�� -> ����ģʽ/8λ���ݿ��/�洢������ģʽ
 *
 * @param       dmax_chy    : DMA��ͨ��, DMA1_Channel1 ~ DMA1_Channel7
 *                            ĳ�������Ӧ�ĸ�DMA, �ĸ�ͨ��, ��ο�<<STM32���Ĳο��ֲ� V10>> 10.3.7��
 *                            ����������ȷ��DMA��ͨ��, ��������ʹ��! 
 * @retval      ��
 */
void dma_init(DMA_Channel_TypeDef* DMAx_CHx)
{
    __HAL_RCC_DMA1_CLK_ENABLE();                                /* DMA1ʱ��ʹ�� */
    
    __HAL_LINKDMA(&g_uart1_handle, hdmatx, g_dma_handle);           /* ��DMA��USART1��ϵ����(����DMA) */
    
    /* Tx DMA���� */
    g_dma_handle.Instance = DMAx_CHx;                               /* USART1_TXʹ�õ�DMAͨ��Ϊ: DMA1_Channel4 */
    g_dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;             /* DIR = 1 , �洢��������ģʽ */
    g_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;                 /* ���������ģʽ */
    g_dma_handle.Init.MemInc = DMA_MINC_ENABLE;                     /* �洢������ģʽ */
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    /* �������ݳ���:8λ */
    g_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;       /* �洢�����ݳ���:8λ */
    g_dma_handle.Init.Mode = DMA_NORMAL;                            /* DMAģʽ:����ģʽ */
    g_dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;               /* �е����ȼ� */

    HAL_DMA_Init(&g_dma_handle);
}
