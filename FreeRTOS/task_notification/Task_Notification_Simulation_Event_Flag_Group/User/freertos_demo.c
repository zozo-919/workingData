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


/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO         3
#define TASK2_STACK_SIZE   128
TaskHandle_t    task2_handler;
void task2( void * pvParameters );

/******************************************************************************************************/
#define EVENTBIT_0  (1 << 0)
#define EVENTBIT_1  (1 << 1)
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


void start_task( void * pvParameters )
{
    taskENTER_CRITICAL();               /* �����ٽ��� */
    xTaskCreate((TaskFunction_t         )   task1,
                (char *                 )   "task1",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &task1_handler );
                
    xTaskCreate((TaskFunction_t         )   task2,
                (char *                 )   "task2",
                (configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK2_PRIO,
                (TaskHandle_t *         )   &task2_handler );
                             
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* �˳��ٽ��� */
}

/* ����һ����������ֵ֪ͨ*/
void task1( void * pvParameters )
{
    uint8_t key = 0;
    while(1) 
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            printf("��bit0λ��1\r\n");
            xTaskNotify( task2_handler, EVENTBIT_0, eSetBits );
        }else if(key == KEY1_PRES)
        {
            printf("��bit1λ��1\r\n");
            xTaskNotify( task2_handler, EVENTBIT_1, eSetBits );
        }
        vTaskDelay(10);
    }
}

/* ���������������ֵ֪ͨ */
void task2( void * pvParameters )
{
    uint32_t notify_val = 0,event_bit = 0;
    while(1)
    {
        xTaskNotifyWait( 0, 0xFFFFFFFF, &notify_val, portMAX_DELAY );
        if(notify_val & EVENTBIT_0)
        {
            event_bit |= EVENTBIT_0;
        }
        if(notify_val & EVENTBIT_1)
        {
            event_bit |= EVENTBIT_1;
        }
        if(event_bit == (EVENTBIT_0|EVENTBIT_1))
        {
            printf("����֪ͨģ���¼���־����ճɹ�����\r\n");
            event_bit = 0;
        }
    }
}
