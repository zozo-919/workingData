/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    ����ʵ��
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


UART_HandleTypeDef g_uart1_handle;
uint8_t g_rx_buffer;             /* ���ڽ��ջ��� */

/**
 * @brief       ���ڳ�ʼ������
 * @param       baudrate: ������
 * @retval      ��
 */
void usart_init(uint32_t baudrate)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();                           /* ʹ�ܴ���TX/RX��ʱ�� */
    __HAL_RCC_USART1_CLK_ENABLE();                          /* ʹ�ܴ���ʱ�� */

    gpio_init_struct.Pin = GPIO_PIN_9;                      /* ���ڷ������ź� */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO�ٶ�����Ϊ���� */
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
            
    gpio_init_struct.Pin = GPIO_PIN_10;                     /* ����RX�� ģʽ���� */
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;    
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);                /* ����RX�� �������ó�����ģʽ */
        
    /*UART ��ʼ������*/
    g_uart1_handle.Instance = USART1;                       /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                /* ������ */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;    /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;         /* һ��ֹͣλ */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;          /* ����żУ��λ */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;    /* ��Ӳ������ */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;             /* �շ�ģʽ */
    HAL_UART_Init(&g_uart1_handle);                         /* HAL_UART_Init()��ʹ��UART1 */
}

int main(void)
{
    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */
    led_init();                                             /* ��ʼ��LED */
    
    while (1)
    {
        if(HAL_UART_Receive(&g_uart1_handle, (uint8_t*)&g_rx_buffer, 1, 100) == HAL_OK)      /* ���յ�������? */
        {
            if (g_rx_buffer == 0x01)
            {
                LED0_TOGGLE();                              /* ��תLED */
                
                HAL_UART_Transmit(&g_uart1_handle, (uint8_t *)"OK", 2, 1000);                /* ���ͽ��յ������� */
                while(__HAL_UART_GET_FLAG(&g_uart1_handle, UART_FLAG_TC) != SET);            /* �ȴ����ͽ��� */
            }
        }
        delay_ms(10);
    }
}
