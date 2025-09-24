#include "./USMART/usmart.h"
#include "./USMART/usmart_str.h"

/******************************************************************************************/
/* �û�������
 * ������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����)
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/LCD/ltdc.h"
#include "./BSP/SDRAM/sdram.h"
#include "./MALLOC/malloc.h"


/* �������б��ʼ��(�û��Լ����)
 * �û�ֱ������������Ҫִ�еĺ�����������Ҵ�
 */
struct _m_usmart_nametab usmart_nametab[] =
{
#if USMART_USE_WRFUNS == 1      /* ���ʹ���˶�д���� */
    (void *)read_addr, "uint32_t read_addr(uint32_t addr)",
    (void *)write_addr, "void write_addr(uint32_t addr,uint32_t val)",
#endif
    (void *)delay_ms, "void delay_ms(uint16_t nms)",
    (void *)delay_us, "void delay_us(uint32_t nus)",
        
    (void *)lcd_clear, "void lcd_clear(uint16_t color)",
    (void *)lcd_fill, "void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)",
    (void *)lcd_draw_line, "void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)",
    (void *)lcd_draw_circle, "void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)",
    (void *)lcd_draw_rectangle, "void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)",
        
    (void *)lcd_show_num, "void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color)",
    (void *)lcd_show_xnum, "void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color)",
    (void *)lcd_show_string, "void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)",
    (void *)lcd_draw_point, "void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)",
    (void *)lcd_read_point, "uint16_t lcd_read_point(uint16_t x, uint16_t y)",
    (void *)lcd_display_dir, "void lcd_display_dir(uint8_t dir)",

    (void *)ltdc_switch, "void ltdc_switch(uint8_t sw)",
    (void *)ltdc_layer_switch, "void ltdc_layer_switch(uint8_t layerx, uint8_t sw)", 
    (void *)ltdc_select_layer, "void ltdc_select_layer(uint8_t layerx)", 
    (void *)ltdc_display_dir, "void ltdc_display_dir(uint8_t dir)",
    (void *)ltdc_draw_point, "void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color)", 
    (void *)ltdc_read_point, "uint32_t ltdc_read_point(uint16_t x, uint16_t y)",
    (void *)ltdc_fill, "void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)",
    (void *)ltdc_layer_window_config, "void ltdc_layer_window_config(uint8_t layerx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)",
    (void *)ltdc_clear, "void ltdc_clear(uint32_t color)", 

#if USMART_USE_WRFUNS == 1 /* ���ʹ���˶�д���� */
    (void *)read_addr, "uint32_t read_addr(uint32_t addr)",
    (void *)write_addr, "void write_addr(uint32_t addr, uint32_t val)",
#endif
    (void *)delay_ms, "void delay_ms(uint16_t nms)",
    (void *)delay_us, "void delay_us(uint32_t nus)",

    (void *)mymalloc, "void *mymalloc(uint8_t memx, uint32_t size)",
    (void *)myfree, "void myfree(uint8_t memx, void *ptr)",
};


/******************************************************************************************/

/* �������ƹ�������ʼ��
 * �õ������ܿغ���������
 * �õ�����������
 */
struct _m_usmart_dev usmart_dev =
{
    usmart_nametab,
    usmart_init,
    usmart_cmd_rec,
    usmart_exe,
    usmart_scan,
    sizeof(usmart_nametab) / sizeof(struct _m_usmart_nametab), /* �������� */
    0,      /* �������� */
    0,      /* ����ID */
    1,      /* ������ʾ����,0,10����;1,16���� */
    0,      /* ��������.bitx:,0,����;1,�ַ��� */
    0,      /* ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ�� */
    0,      /* �����Ĳ���,��ҪPARM_LEN��0��ʼ�� */
};



















