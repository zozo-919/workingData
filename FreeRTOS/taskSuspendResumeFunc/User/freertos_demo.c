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
static StaticTask_t startTaskTCB;
static StackType_t startTaskStack[configTIMER_TASK_STACK_DEPTH];

#define TASK1_STACK_SIZE  128
#define TASK1_PRIO 2
TaskHandle_t task1_fucn_handler;
static StaticTask_t task1TCB;
static StackType_t task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE  128
#define TASK2_PRIO 3
TaskHandle_t task2_fucn_handler;
static StaticTask_t task2TCB;
static StackType_t task2Stack[TASK2_STACK_SIZE];

#define TASK3_STACK_SIZE  128
#define TASK3_PRIO 4
TaskHandle_t task3_fucn_handler;
static StaticTask_t task3TCB;
static StackType_t task3Stack[TASK3_STACK_SIZE];

void start_task(void* pvParameters);
void task1(void* pvParameters);
void task2(void* pvParameters);
void task3(void* pvParameters);


/* ���������ڴ���� */
StaticTask_t idleTaskTcb;
StackType_t idleTaskStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idleTaskTcb;
    *ppxIdleTaskStackBuffer = idleTaskStack;
    pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;

}

/* �����ʱ�������ڴ���� */
static StaticTask_t timerTaskTCB;
static StackType_t timerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
    *ppxTimerTaskTCBBuffer = &timerTaskTCB;
    *ppxTimerTaskStackBuffer = timerStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void freertos_demo(void)
{
    // ������ʼ����
    start_task_handler = xTaskCreateStatic((TaskFunction_t) start_task, (char * ) "start_task", \
                (uint32_t) START_TASK_STACK_SIZE, (void *) NULL, (UBaseType_t) START_TASK_PRIO, \
                (StackType_t *) startTaskStack, (StaticTask_t *) &startTaskTCB);

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
        task1_fucn_handler = xTaskCreateStatic((TaskFunction_t) task1, (char * ) "task1", \
                (uint32_t) TASK1_STACK_SIZE, (void *) NULL, (UBaseType_t) TASK1_PRIO, \
                (StackType_t *) task1Stack, (StaticTask_t *) &task1TCB);
        
        task2_fucn_handler = xTaskCreateStatic((TaskFunction_t) task2, (char * ) "task2", \
                (uint32_t) TASK2_STACK_SIZE, (void *) NULL, (UBaseType_t) TASK2_PRIO, \
                (StackType_t *) task2Stack, (StaticTask_t *) &task2TCB);

        task3_fucn_handler = xTaskCreateStatic((TaskFunction_t) task3, (char * ) "task3", \
                (uint32_t) TASK3_STACK_SIZE, (void *) NULL, (UBaseType_t) TASK3_PRIO, \
                (StackType_t *) task3Stack, (StaticTask_t *) &task3TCB);
    
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

/* ������ �жϰ���KEY0 ����ʱ����task1 KEY1�����������лָ�task1  
 * KEY2�������ж��лָ�task1(�ⲿ�ж� ������ ��/Drivers/BSP/�� ������ˡ�EXIT�� �ⲿ�ж������ļ���
 * ���޸��� /Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c �� 173�е� HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
 */
void task3(void* pvParameters)
{
    uint8_t key = 0;
    while (1)
    {
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
            vTaskSuspend(task1_fucn_handler);
                        
        } else if (key == KEY1_PRES)
        {
            vTaskResume(task1_fucn_handler);
        }
        
        vTaskDelay(10);
    }
}
