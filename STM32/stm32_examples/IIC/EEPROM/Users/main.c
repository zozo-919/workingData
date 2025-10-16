
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ATK_24C02/atk_24c02.h"

uint8_t a_buf[] = {"abcdefg"};

int main(void)
{
    uint8_t key = 0;
//    uint8_t reveive = 0;
    uint8_t b_buf[100] = {0};
    
    HAL_Init();                                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                         /* 设置时钟, 72Mhz */
    delay_init(72);                                             /* 延时初始化 */
    usart_init(115200);                                         /* 初始化串口 */
    led_init();                                                 /* 初始化LED */
    key_init();                                                 /* 初始化按键 */
    atk_24c02_init();
    
    while (1)
    {
        key = key_scan(0);                                      /* 扫描按键 */
        
        switch (key)
        {
            case KEY0_PRES:                                     /* KEY0被按下 */
            {
                printf("写入数据\r\n");
//                atk_24cxx_write_one_byte(0x01,  0xbb);
                atk_24cxx_write(0x00, a_buf, sizeof(a_buf));
                break;
            }
            case WKUP_PRES:                                     /* KEY_UP被按下 */
            {
                printf("读取数据\r\n");
//                reveive = atk_24cxx_read_one_byte(0x01);
                atk_24cxx_read(0x00, b_buf, sizeof(a_buf));
                printf("b_buf: %s\r\n", b_buf);
                break;
            }
            default:
            {
                break;
            }
        }
        
        delay_ms(10);
    }
}
