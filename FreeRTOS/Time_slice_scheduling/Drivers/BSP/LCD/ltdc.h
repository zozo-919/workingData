/**
 ****************************************************************************************************
 * @file        ltdc.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LTDC ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20220420
 * ��һ�η���
 *
 ****************************************************************************************************
 */


#ifndef _LCD_H
#define _LCD_H

#include "./SYSTEM/sys/sys.h"

/* LCD LTDC��Ҫ������ */
typedef struct  
{
    uint32_t pwidth;      /* LCD���Ŀ��,�̶�����,������ʾ����ı�,���Ϊ0,˵��û���κ�RGB������ */
    uint32_t pheight;     /* LCD���ĸ߶�,�̶�����,������ʾ����ı� */
    uint16_t hsw;         /* ˮƽͬ����� */
    uint16_t vsw;         /* ��ֱͬ����� */
    uint16_t hbp;         /* ˮƽ���� */
    uint16_t vbp;         /* ��ֱ���� */
    uint16_t hfp;         /* ˮƽǰ�� */
    uint16_t vfp;         /* ��ֱǰ��  */
    uint8_t activelayer;  /* ��ǰ����:0/1 */
    uint8_t dir;          /* 0,����;1,����; */
    uint16_t width;       /* LCD��� */
    uint16_t height;      /* LCD�߶� */
    uint32_t pixsize;     /* ÿ��������ռ�ֽ��� */
}_ltdc_dev; 

extern _ltdc_dev lcdltdc;                   /* ����LCD LTDC���� */
extern LTDC_HandleTypeDef g_ltdc_handle;    /* LTDC��� */
extern DMA2D_HandleTypeDef g_dma2d_handle;  /* DMA2D��� */

#define LCD_PIXEL_FORMAT_ARGB8888       0X00    
#define LCD_PIXEL_FORMAT_RGB888         0X01    
#define LCD_PIXEL_FORMAT_RGB565         0X02       
#define LCD_PIXEL_FORMAT_ARGB1555       0X03      
#define LCD_PIXEL_FORMAT_ARGB4444       0X04     
#define LCD_PIXEL_FORMAT_L8             0X05     
#define LCD_PIXEL_FORMAT_AL44           0X06     
#define LCD_PIXEL_FORMAT_AL88           0X07      

/******************************************************************************************/
/*�û��޸����ò���:

 * ������ɫ���ظ�ʽ,һ����RGB565 */
#define LCD_PIXFORMAT       LCD_PIXEL_FORMAT_RGB565
/* ����Ĭ�ϱ�������ɫ */
#define LTDC_BACKLAYERCOLOR           0X00000000
/* LCD֡�������׵�ַ,���ﶨ����SDRAM����. */
#define LCD_FRAME_BUF_ADDR            0XC0000000  

void ltdc_switch(uint8_t sw);             /* LTDC���� */
void ltdc_layer_switch(uint8_t layerx, uint8_t sw);    /* �㿪�� */
void ltdc_select_layer(uint8_t layerx);     /* ��ѡ�� */
void ltdc_display_dir(uint8_t dir);         /* ��ʾ������� */
void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color);/* ���㺯�� */
uint32_t ltdc_read_point(uint16_t x, uint16_t y);            /* ���㺯�� */
void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);           /* ���ε�ɫ��亯�� */
void ltdc_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);    /* ���β�ɫ��亯�� */
void ltdc_clear(uint32_t color);            /* �������� */
uint8_t ltdc_clk_set(uint32_t pllsain, uint32_t pllsair, uint32_t pllsaidivr);   /* LTDCʱ������ */
void ltdc_layer_window_config(uint8_t layerx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);   /* LTDC�㴰������ */
void ltdc_layer_parameter_config(uint8_t layerx, uint32_t bufaddr, uint8_t pixformat, uint8_t alpha, uint8_t alpha0, uint8_t bfac1, uint8_t bfac2, uint32_t bkcolor);  /* LTDC������������ */
uint16_t ltdc_panelid_read(void);         /* LCD ID��ȡ���� */
void ltdc_init(void);                     /* LTDC��ʼ������ */


#endif 
