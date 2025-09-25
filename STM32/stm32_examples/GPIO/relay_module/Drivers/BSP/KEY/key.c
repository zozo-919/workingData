/**
 ****************************************************************************************************
 * @file        key.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       按键输入 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 M48Z-M3最小系统板STM32F103版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    gpio_init_struct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    
    gpio_init_struct.Pin = GPIO_PIN_7;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);
    
    gpio_init_struct.Pin = GPIO_PIN_2;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
}

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): KEY3 > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY0_PRES, 1, KEY0按下
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 *              KEY3_PRES, 4, KEY3按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;                          /* 按键松开标志 */
    uint8_t key_val = 0;
    
    if (mode == 1)                                      /* 支持连按 */
    {
        key_up = 1;
    }
    
    if (key_up && (KEY0 == 1 || KEY1 == 1 || KEY2 == 1  || KEY3 == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 1)  key_val = KEY0_PRES;

        if (KEY1 == 1)  key_val = KEY1_PRES;

        if (KEY2 == 1)  key_val = KEY2_PRES;

        if (KEY3 == 0)  key_val = KEY3_PRES;
    }
    else if (KEY0 == 0 && KEY1 == 0 && KEY2 == 0 && KEY3 == 1) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }
    
    return key_val;                                     /* 返回键值 */
}




