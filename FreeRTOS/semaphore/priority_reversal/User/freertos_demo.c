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
#include "semphr.h"
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
TaskHandle_t    low_task_handler;
void low_task( void * pvParameters );


/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO         3
#define TASK2_STACK_SIZE   128
TaskHandle_t    middle_task_handler;
void middle_task( void * pvParameters );


/* TASK3 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK3_PRIO         4
#define TASK3_STACK_SIZE   128
TaskHandle_t    high_task_handler;
void high_task( void * pvParameters );

/******************************************************************************************************/
QueueHandle_t semphore_handle;
/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{    
    semphore_handle = xSemaphoreCreateBinary();
    if(semphore_handle != NULL)
    {
        printf("��ֵ�ź��������ɹ�������\r\n");
    }
    xSemaphoreGive(semphore_handle);        /* �ͷ�һ���ź��� */
    
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
    xTaskCreate((TaskFunction_t         )   low_task,
                (char *                 )   "low_task",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &low_task_handler );
                
    xTaskCreate((TaskFunction_t         )   middle_task,
                (char *                 )   "middle_task",
                (configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK2_PRIO,
                (TaskHandle_t *         )   &middle_task_handler );
                
    xTaskCreate((TaskFunction_t         )   high_task,
                (char *                 )   "high_task",
                (configSTACK_DEPTH_TYPE )   TASK3_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK3_PRIO,
                (TaskHandle_t *         )   &high_task_handler );
                             
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* �˳��ٽ��� */
}

/* ����һ�������ȼ����� */
void low_task( void * pvParameters )
{
    while(1) 
    {
        printf("low_task��ȡ�ź���\r\n");
        xSemaphoreTake(semphore_handle,portMAX_DELAY);
        printf("low_task�������У�����\r\n");
        delay_ms(3000);
        printf("low_task�ͷ��ź���\r\n");
        xSemaphoreGive(semphore_handle); 
        vTaskDelay(1000);
    }
}

/* ������������ȼ����� */
void middle_task( void * pvParameters )
{
    while(1)
    {
        printf("middle_task�������У�����\r\n");
        vTaskDelay(1000);
    }
}

/* �������������ȼ����� */
void high_task( void * pvParameters )
{
    while(1)
    {
        printf("high_task��ȡ�ź���\r\n");
        xSemaphoreTake(semphore_handle,portMAX_DELAY);
        printf("high_task�������У�����\r\n");
        delay_ms(1000);
        printf("high_task�ͷ��ź���\r\n");
        xSemaphoreGive(semphore_handle); 
        vTaskDelay(1000);
    }
}


