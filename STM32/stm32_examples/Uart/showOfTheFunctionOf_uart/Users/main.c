/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    串口实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 M48Z-M3最小系统板STM32F103版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


UART_HandleTypeDef g_uart1_handle;
uint8_t g_rx_buffer;             /* 串口接收缓冲 */

/**
 * @brief       串口初始化函数
 * @param       baudrate: 波特率
 * @retval      无
 */
void usart_init(uint32_t baudrate)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();                           /* 使能串口TX/RX脚时钟 */
    __HAL_RCC_USART1_CLK_ENABLE();                          /* 使能串口时钟 */

    gpio_init_struct.Pin = GPIO_PIN_9;                      /* 串口发送引脚号 */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO速度设置为高速 */
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
            
    gpio_init_struct.Pin = GPIO_PIN_10;                     /* 串口RX脚 模式设置 */
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;    
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);                /* 串口RX脚 必须设置成输入模式 */
        
    /*UART 初始化设置*/
    g_uart1_handle.Instance = USART1;                       /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;    /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;         /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;          /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;    /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;             /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                         /* HAL_UART_Init()会使能UART1 */
}

int main(void)
{
    HAL_Init();                                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
    delay_init(72);                                         /* 延时初始化 */
    usart_init(115200);                                     /* 初始化串口 */
    led_init();                                             /* 初始化LED */
    
    while (1)
    {
        if(HAL_UART_Receive(&g_uart1_handle, (uint8_t*)&g_rx_buffer, 1, 100) == HAL_OK)      /* 接收到了数据? */
        {
            if (g_rx_buffer == 0x01)
            {
                LED0_TOGGLE();                              /* 翻转LED */
                
                HAL_UART_Transmit(&g_uart1_handle, (uint8_t *)"OK", 2, 1000);                /* 发送接收到的数据 */
                while(__HAL_UART_GET_FLAG(&g_uart1_handle, UART_FLAG_TC) != SET);            /* 等待发送结束 */
            }
        }
        delay_ms(10);
    }
}
