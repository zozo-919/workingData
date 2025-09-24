
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"
#include "freertos_demo.h"
#include "./BSP/EXTI/exti.h"

int main(void)
{
    HAL_Init();                                 /* ???HAL? */
    sys_stm32_clock_init(360, 25, 2, 8);        /* ????,180Mhz */
    delay_init(180);                            /* ????? */
    usart_init(115200);                         /* ??????115200 */
    led_init();                                 /* ???LED */
    key_init();                                 /* ????? */
    sdram_init();                               /* SRAM??? */

    lcd_init();                                 /* ???LCD */
    
    /* ???? ??? */
    extix_init();                               
    
    my_mem_init(SRAMIN);                        /* ???????? */
    my_mem_init(SRAMEX);                        /* ???????? */
    my_mem_init(SRAMCCM);                       /* ???CCM??? */
    
    freertos_demo();
}
