
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"

const char *SRAM_NAME_BUF[SRAMBANK] = {" SRAMIN  ", " SRAMCCM ", " SRAMEX  "};

int main(void)
{
    uint8_t paddr[20];                 /* ���P Addr:+p��ַ��ASCIIֵ */
    uint16_t memused = 0;
    uint8_t key;
    uint8_t i = 0;
    uint8_t *p = 0;
    uint8_t *tp = 0;
    uint8_t sramx = 0;                  /* Ĭ��Ϊ�ڲ�sram */

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
    
    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "MALLOC TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "KEY0:Malloc & WR & Show", RED);
    lcd_show_string(30, 130, 200, 16, 16, "KEY_UP:SRAMx KEY1:Free", RED);
    lcd_show_string(60, 160, 200, 16, 16, " SRAMIN ", BLUE);
    lcd_show_string(30, 176, 200, 16, 16, "SRAMIN   USED:", BLUE);
    lcd_show_string(30, 192, 200, 16, 16, "SRAMCCM  USED:", BLUE);
    lcd_show_string(30, 208, 200, 16, 16, "SRAMEX   USED:", BLUE);
    
    while (1)
    {
        key = key_scan(0);      /* ��֧������ */

        switch (key)
        {
            case KEY0_PRES:     /* KEY0���� */
                p = mymalloc(sramx, 2048);  /* ����2K�ֽ�,��д������,��ʾ��lcd��Ļ���� */

                if (p != NULL)
                {
                    sprintf((char *)p, "Memory Malloc Test%03d", i);            /* ��pд��һЩ���� */
                    lcd_show_string(30, 260, 209, 16, 16, (char *)p, BLUE);     /* ��ʾP������ */
                }
                break;

            case KEY1_PRES:         /* KEY1���� */
                myfree(sramx, p);   /* �ͷ��ڴ� */
                p = 0;              /* ָ��յ��? */
                break;

            case WKUP_PRES:         /* KEY UP���� */
                sramx++;

                if (sramx >= SRAMBANK) sramx = 0;

                lcd_show_string(60, 160, 200, 16, 16, (char *)SRAM_NAME_BUF[sramx], BLUE);
                break;
        }

        if (tp != p)
        {
            tp = p;
            sprintf((char *)paddr, "P Addr:0X%08X", (uint32_t)tp);
            lcd_show_string(30, 240, 209, 16, 16, (char *)paddr, BLUE); /* ��ʾp�ĵ�ַ */

            if (p)
            {
                lcd_show_string(30, 260, 280, 16, 16, (char *)p, BLUE); /* ��ʾP������ */
            }
            else 
            {
                lcd_fill(30, 260, 209, 296, WHITE);    /* p=0,������? */
            }
        }

        delay_ms(10);
        i++;

        if ((i % 20) == 0)  /* DS0��˸. */
        {
            memused = my_mem_perused(SRAMIN);
            sprintf((char *)paddr, "%d.%01d%%", memused / 10, memused % 10);
            lcd_show_string(30 + 112, 176, 200, 16, 16, (char *)paddr, BLUE);   /* ��ʾ�ڲ��ڴ�ʹ���� */
            
            memused = my_mem_perused(SRAMCCM);
            sprintf((char *)paddr, "%d.%01d%%", memused / 10, memused % 10);
            lcd_show_string(30 + 112, 192, 200, 16, 16, (char *)paddr, BLUE);   /* ��ʾCCM�ڴ�ʹ���� */
            
            memused = my_mem_perused(SRAMEX);
            sprintf((char *)paddr, "%d.%01d%%", memused / 10, memused % 10);
            lcd_show_string(30 + 112, 208, 200, 16, 16, (char *)paddr, BLUE);   /* ��ʾ�ⲿ�ڴ�ʹ���� */
            
            LED0_TOGGLE();  /* LED0��˸ */
        }
    }
}
