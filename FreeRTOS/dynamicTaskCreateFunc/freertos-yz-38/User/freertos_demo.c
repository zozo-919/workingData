/**
 * @file    freertos_demo.c
 * @author  Zozo@
 * @brief   ʹ�ö�̬���������� ��������
 * @version 1.0
 * @date    2025-08-10
 */

#include "freertos_demo.h"
#include "../Drivers/SYSTEM/usart/usart.h"
#include "../Drivers/BSP/LED/led.h"
#include "../Drivers/BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"


#include "FreeRTOS.h"
#include "task.h"

#define START_TASK_STACK_SIZE  128
#define START_TASK_PRIO 1
TaskHandle_t start_task_handler;

#define TASK1_STACK_SIZE  128
#define TASK1_PRIO 2
TaskHandle_t task1_fucn_handler;

#define TASK2_STACK_SIZE  128
#define TASK2_PRIO 3
TaskHandle_t task2_fucn_handler;

#define TASK3_STACK_SIZE  128
#define TASK3_PRIO 4
TaskHandle_t task3_fucn_handler;

void start_task(void* pvParameters);
void task1(void* pvParameters);
void task2(void* pvParameters);
void task3(void* pvParameters);


void freertos_demo(void)
{
    xTaskCreate((TaskFunction_t) start_task, (char * )"start_task", (configSTACK_DEPTH_TYPE) START_TASK_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) START_TASK_PRIO, (TaskHandle_t *) &start_task_handler );
    
    // �����������
    vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
    /**�ٽ����൱���ǹر���������������� �����л��Ͳ������ ֻ���˳��ٽ����� �ŻῪʼ�����л� 
     * �˳��ٽ����� ��ʱ ����ִ�еľ������ȼ���ߵ�task3 ��task3ִ�е���ʱ��λ��ʱ
     * task2�ŻῪʼִ�� Ȼ����task1
     */
    taskENTER_CRITICAL();   /* �����ٽ���*/
    xTaskCreate((TaskFunction_t) task1, (char * )"task1", (configSTACK_DEPTH_TYPE) TASK1_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK1_PRIO, (TaskHandle_t *) &task1_fucn_handler );

    xTaskCreate((TaskFunction_t) task2, (char * )"task2", (configSTACK_DEPTH_TYPE) TASK2_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK2_PRIO, (TaskHandle_t *) &task2_fucn_handler );
    
    xTaskCreate((TaskFunction_t) task3, (char * )"task3", (configSTACK_DEPTH_TYPE) TASK3_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK3_PRIO, (TaskHandle_t *) &task3_fucn_handler );
    
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();    /* �˳��ٽ��� */
}

/* ����һ ʵ��LED0ÿ500ms��תһ��*/
void task1(void* pvParameters)
{
    while (1)
    {
        LED0_TOGGLE();
        vTaskDelay(500);
    }
    

}

/* ����� ʵ��LED1ÿ500ms��תһ��*/
void task2(void* pvParameters)
{
    while (1)
    {
        LED1_TOGGLE();
        vTaskDelay(500);
    }
    
    
}

/* ������ �жϰ���KEY0 ����ʱɾ��task1*/
void task3(void* pvParameters)
{
    uint8_t key = 0;
    while (1)
    {
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
            if (!task1_fucn_handler)
            {
                vTaskDelete(task1_fucn_handler);
                task1_fucn_handler = NULL;

            }
            
        }
        vTaskDelay(10);
    }
}
