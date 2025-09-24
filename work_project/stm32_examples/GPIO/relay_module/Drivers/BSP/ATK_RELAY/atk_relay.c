#include "./BSP/ATK_RELAY/atk_relay.h"

/**
 * @brief       ��ʼ���̵���ģ��
 * @param       ��
 * @retval      ��
 */
void atk_relay_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_init_struct.Pin = GPIO_PIN_3;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    
    /* �Ͽ��̵������� */
    HAL_GPIO_WritePin(GPIOA,  GPIO_PIN_3, GPIO_PIN_RESET);
}







