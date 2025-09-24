
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"

const char *SRAM_NAME_BUF[SRAMBANK] = {" SRAMIN  ", " SRAMCCM ", " SRAMEX  "};

int main(void)
{
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(360, 25, 2, 8);        /* ����ʱ��,180Mhz */
    delay_init(180);                            /* ��ʱ��ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                                 /* ��ʼ��LED */
    key_init();                                 /* ��ʼ������ */
    sdram_init();                               /* SRAM��ʼ�� */
    lcd_init();                                 /* ��ʼ��LCD */

    my_mem_init(SRAMIN);                        /* ��ʼ���ڲ��ڴ��? */
    my_mem_init(SRAMEX);                        /* ��ʼ���ⲿ�ڴ��? */
    my_mem_init(SRAMCCM);                       /* ��ʼ��CCM�ڴ��? */

    freertos_demo();
}
