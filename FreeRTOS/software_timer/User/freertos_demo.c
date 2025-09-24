/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ��ֲʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� F407���������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"
#include "./MALLOC/malloc.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE   128
TaskHandle_t    start_task_handler;
void start_task( void * pvParameters );

/* TASK1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK1_PRIO         2
#define TASK1_STACK_SIZE   128
TaskHandle_t    task1_handler;
void task1( void * pvParameters );

void timer1_callback( TimerHandle_t pxTimer );
void timer2_callback( TimerHandle_t pxTimer );
/******************************************************************************************************/

/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{    
    xTaskCreate((TaskFunction_t         )   start_task,
                (char *                 )   "start_task",
                (configSTACK_DEPTH_TYPE )   START_TASK_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   START_TASK_PRIO,
                (TaskHandle_t *         )   &start_task_handler );
    vTaskStartScheduler();
}

TimerHandle_t timer1_handle = 0;    /* ���ζ�ʱ�� */
TimerHandle_t timer2_handle = 0;    /* ���ڶ�ʱ�� */

void start_task( void * pvParameters )
{
    taskENTER_CRITICAL();               /* �����ٽ��� */
    
    /* ���ζ�ʱ�� */
    timer1_handle = xTimerCreate( "timer1", 
                                    500,
                                    pdFALSE,
                                    (void *)1,
                                    timer1_callback );
                            
    /* ���ڶ�ʱ�� */
    timer2_handle = xTimerCreate( "timer2", 
                                    2000,
                                    pdTRUE,
                                    (void *)2,
                                    timer2_callback );
                                    
    xTaskCreate((TaskFunction_t         )   task1,
                (char *                 )   "task1",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &task1_handler );
                                             
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* �˳��ٽ��� */
}

/* ����һ������ɨ�貢���������ʱ�� */
void task1( void * pvParameters )
{
    uint8_t key = 0;
    while(1) 
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            xTimerStart(timer1_handle,portMAX_DELAY);
            xTimerStart(timer2_handle,portMAX_DELAY);
        }else if(key == KEY1_PRES)
        {
            xTimerStop(timer1_handle,portMAX_DELAY);
            xTimerStop(timer2_handle,portMAX_DELAY);
        }
        vTaskDelay(10);
    }
}

/* timer1�ĳ�ʱ�ص����� */
void timer1_callback( TimerHandle_t pxTimer )
{
    static uint32_t timer = 0;
    printf("timer1�����д�����%d\r\n",++timer);
}

/* timer2�ĳ�ʱ�ص����� */
void timer2_callback( TimerHandle_t pxTimer )
{
    static uint32_t timer = 0;
    printf("timer2�����д�����%d\r\n",++timer);
}


