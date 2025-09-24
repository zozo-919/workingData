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
#include "queue.h"
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

/* TASK3 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK3_PRIO         4
#define TASK3_STACK_SIZE   128
TaskHandle_t    task3_handler;
void task3( void * pvParameters );
/******************************************************************************************************/
QueueHandle_t key_queue;        /* С���ݾ�� */
QueueHandle_t big_date_queue;   /* �����ݾ�� */
char buff[100] = {"����һ�������飬�������� 124214 uhsidhaksjhdklsadhsaklj"};
/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_demo(void)
{    
    /* ���еĴ��� */
    key_queue = xQueueCreate( 2, sizeof(uint8_t) );
    if(key_queue != NULL)
    {
        printf("key_queue���д����ɹ�����\r\n");
    }else printf("key_queue���д���ʧ�ܣ���\r\n");
    
    big_date_queue = xQueueCreate( 1, sizeof(char *) );
    if(big_date_queue != NULL)
    {
        printf("big_date_queue���д����ɹ�����\r\n");
    }else printf("big_date_queue���д���ʧ�ܣ���\r\n");
    
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
               
    xTaskCreate((TaskFunction_t         )   task3,
                (char *                 )   "task3",
                (configSTACK_DEPTH_TYPE )   TASK3_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK3_PRIO,
                (TaskHandle_t *         )   &task3_handler );                
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* �˳��ٽ��� */
}

/* ����һ��ʵ����� */
void task1( void * pvParameters )
{
    uint8_t key = 0;
    char * buf;
    BaseType_t   err = 0;
    buf = &buff[0]; /* buf = &buff[0] */
    while(1) 
    {
        key = key_scan(0);
        if(key == KEY0_PRES || key == KEY1_PRES)
        {
            err = xQueueSend( key_queue, &key, portMAX_DELAY );
            if(err != pdTRUE)
            {
                printf("key_queue���з���ʧ��\r\n");
            }
        }else if(key == WKUP_PRES)
        {
            err = xQueueSend( big_date_queue, &buf, portMAX_DELAY );
            if(err != pdTRUE)
            {
                printf("key_queue���з���ʧ��\r\n");
            }
        }
        vTaskDelay(10);
    }
}

/* �������С���ݳ��� */
void task2( void * pvParameters )
{
    uint8_t key = 0;
    BaseType_t err = 0;
    while(1)
    {
        err = xQueueReceive( key_queue,&key,portMAX_DELAY);
        if(err != pdTRUE)
        {
            printf("key_queue���ж�ȡʧ��\r\n");
        }else 
        {
            printf("key_queue��ȡ���гɹ������ݣ�%d\r\n",key);
        }
    }
}

/* �������������ݳ��� */
void task3( void * pvParameters )
{
    char * buf;
    BaseType_t err = 0;
    while(1)
    {
        err = xQueueReceive( big_date_queue,&buf,portMAX_DELAY);
        if(err != pdTRUE)
        {
            printf("big_date_queue���ж�ȡʧ��\r\n");
        }else 
        {
            printf("���ݣ�%s\r\n",buf);
        }
    }
}

