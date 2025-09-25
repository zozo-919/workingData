/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    DMA����ʵ�飨���������洢����
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

uint8_t buf_a[5] = {'h','e','l','l','o'};
uint8_t buf_b[5];

DMA_HandleTypeDef g_dma_handle;

void dma_init(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    g_dma_handle.Instance = DMA1_Channel1;
    g_dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;
    g_dma_handle.Init.Direction = DMA_MEMORY_TO_MEMORY;
    g_dma_handle.Init.PeriphInc = DMA_PINC_ENABLE;
    g_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    g_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    g_dma_handle.Init.Mode = DMA_NORMAL;
    HAL_DMA_Init(&g_dma_handle);
    
    HAL_DMA_Start(&g_dma_handle, (uint32_t)buf_a, (uint32_t)buf_b, 5);
}

void dma_t_enable(void)
{
    __HAL_DMA_DISABLE(&g_dma_handle);
    g_dma_handle.Instance->CNDTR = 5;
    __HAL_DMA_ENABLE(&g_dma_handle);
}

int main(void)
{
    HAL_Init();                                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                         /* ����ʱ��, 72Mhz */
    delay_init(72);                                             /* ��ʱ��ʼ�� */
    usart_init(115200);                                         /* ��ʼ������ */
    led_init();                                                 /* ��ʼ��LED */
    key_init();                                                 /* ��ʼ������ */
    
    for(uint8_t i = 0; i < 5; i++)
    {
        printf("%c", buf_b[i]);
    }
            
    dma_init();
    
    
    while (1)
    {
        if(key_scan(0) == KEY0_PRES)
        {
            dma_t_enable();
        }
        
        if(__HAL_DMA_GET_FLAG(&g_dma_handle, DMA_FLAG_TC1))
        {
            __HAL_DMA_CLEAR_FLAG(&g_dma_handle, DMA_FLAG_TC1);
            
            for(uint8_t i = 0; i < 5; i++)
            {
                printf("%c", buf_b[i]);
            }
        }
        delay_ms(10);
    }
}
