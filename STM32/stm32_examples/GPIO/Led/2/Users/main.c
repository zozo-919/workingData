/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    新建工程实验-HAL库版本实验
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


int main(void)
{
    GPIO_InitTypeDef  gpio_init_struct;
    
    HAL_Init();                                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
    delay_init(72);                                         /* 延时初始化 */
    usart_init(115200);                                     /* 初始化串口 */

    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    
    __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_AFIO_CLK_ENABLE();        /* 配置AFIO寄存器，需要使能AFIO时钟 */
    __HAL_AFIO_REMAP_SWJ_NOJTAG();      /* 使用SWD下载方式，可使用该宏定义可以释放PA15、PB3、PB4这3个IO口，建议用 */
//    __HAL_AFIO_REMAP_SWJ_DISABLE();   /* 该宏定义会释放PA13、PA14、PA15、PB3、PB4这5个IO口，导致下一次下载报通信失败错误，不建议用 */
    
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);
    

    while(1)
    { 
        /* 二灯争艳 */
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
        delay_ms(200);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        delay_ms(200);
    }
}
