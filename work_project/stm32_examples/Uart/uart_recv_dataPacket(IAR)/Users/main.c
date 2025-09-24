/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2024-11-01
 * @brief    ���ڽ������ݰ� ʵ��
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

#include <stdio.h>

UART_HandleTypeDef g_uart_init_handle;

uint8_t rx_data;
uint8_t buf[200];
uint8_t num = 0;
    
void usart_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_init_struct;

    gpio_init_struct.Pin = GPIO_PIN_9;                      /* TX���� */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ���츴����� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);                /* ��ʼ��TX���� */
    
    gpio_init_struct.Pin = GPIO_PIN_10;                     /* RX���� */
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;             /* ����ģʽ */
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);                /* ��ʼ��RX���� */
    
    g_uart_init_handle.Instance = USART1;
    g_uart_init_handle.Init.BaudRate = 115200;
    g_uart_init_handle.Init.WordLength = UART_WORDLENGTH_8B;
    g_uart_init_handle.Init.StopBits = UART_STOPBITS_1;
    g_uart_init_handle.Init.Parity = UART_PARITY_NONE;
    g_uart_init_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    g_uart_init_handle.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&g_uart_init_handle);
    
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);
    __HAL_UART_ENABLE_IT(&g_uart_init_handle, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&g_uart_init_handle, UART_IT_IDLE);
}

void USART1_IRQHandler(void)
{
    if(__HAL_UART_GET_FLAG(&g_uart_init_handle, UART_FLAG_RXNE) != 0)
    {
        if(HAL_UART_Receive(&g_uart_init_handle, &rx_data, 1, 100) == HAL_OK)
        {
            buf[num] = rx_data;
            num++;
        }
    }
    
    if(__HAL_UART_GET_FLAG(&g_uart_init_handle, UART_FLAG_IDLE) != 0)
    {
        LED0_TOGGLE();
        __HAL_UART_CLEAR_IDLEFLAG(&g_uart_init_handle);
        HAL_UART_Transmit(&g_uart_init_handle, buf, num, 100);
        num = 0;
    }
}

int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);     /* �ȴ���һ���ַ�������� */

    USART1->DR = (uint8_t)ch;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}

int main(void)
{
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init();                                           /* ��ʼ������ */
    led_init();                                             /* ��ʼ��LED */
    
    while (1)
    {
        printf("num:%d ", 50);
        delay_ms(1000);
    }
}
