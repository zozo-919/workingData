/**
 * @file    freertos_demo.c
 * @author  Zozo@
 * @brief   使用动态创建任务函数 创建任务
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
    
    // 打开任务调度器
    vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
    /**临界区相当于是关闭任务调度器的作用 任务切换就不会进行 只有退出临界区后 才会开始任务切换 
     * 退出临界区后 此时 最先执行的就是优先级最高的task3 当task3执行到延时的位置时
     * task2才会开始执行 然后是task1
     */
    taskENTER_CRITICAL();   /* 进入临界区*/
    xTaskCreate((TaskFunction_t) task1, (char * )"task1", (configSTACK_DEPTH_TYPE) TASK1_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK1_PRIO, (TaskHandle_t *) &task1_fucn_handler );

    xTaskCreate((TaskFunction_t) task2, (char * )"task2", (configSTACK_DEPTH_TYPE) TASK2_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK2_PRIO, (TaskHandle_t *) &task2_fucn_handler );
    
    xTaskCreate((TaskFunction_t) task3, (char * )"task3", (configSTACK_DEPTH_TYPE) TASK3_STACK_SIZE, \
                (void *) NULL, (UBaseType_t) TASK3_PRIO, (TaskHandle_t *) &task3_fucn_handler );
    
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();    /* 退出临界区 */
}

/* 任务一 实现LED0每500ms翻转一次*/
void task1(void* pvParameters)
{
    while (1)
    {
        LED0_TOGGLE();
        vTaskDelay(500);
    }
    

}

/* 任务二 实现LED1每500ms翻转一次*/
void task2(void* pvParameters)
{
    while (1)
    {
        LED1_TOGGLE();
        vTaskDelay(500);
    }
    
    
}

/* 任务三 判断按键KEY0 按下时删除task1*/
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
