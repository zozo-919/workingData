
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
    
    HAL_Init();                                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                         /* ����ʱ��, 72Mhz */
    delay_init(72);                                             /* ��ʱ��ʼ�� */
    usart_init(115200);                                         /* ��ʼ������ */
    led_init();                                                 /* ��ʼ��LED */
    key_init();                                                 /* ��ʼ������ */
    atk_24c02_init();
    
    while (1)
    {
        key = key_scan(0);                                      /* ɨ�谴�� */
        
        switch (key)
        {
            case KEY0_PRES:                                     /* KEY0������ */
            {
                printf("д������\r\n");
//                atk_24cxx_write_one_byte(0x01,  0xbb);
                atk_24cxx_write(0x00, a_buf, sizeof(a_buf));
                break;
            }
            case WKUP_PRES:                                     /* KEY_UP������ */
            {
                printf("��ȡ����\r\n");
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
