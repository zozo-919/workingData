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


/* 空闲任务内存分配 */
StaticTask_t idleTaskTcb;
StackType_t idleTaskStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idleTaskTcb;
    *ppxIdleTaskStackBuffer = idleTaskStack;
    pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;

}

/* 软件定时器任务内存分配 */
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
    // 创建开始任务
    start_task_handler = xTaskCreateStatic((TaskFunction_t) start_task, (char * ) "start_task", \
                (uint32_t) START_TASK_STACK_SIZE, (void *) NULL, (UBaseType_t) START_TASK_PRIO, \
                (StackType_t *) startTaskStack, (StaticTask_t *) &startTaskTCB);

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

/* 任务三 判断按键KEY0 按下时挂起task1 KEY1按下在任务中恢复task1  
 * KEY2按下在中断中恢复task1(外部中断 这里在 ’/Drivers/BSP/‘ 中添加了“EXIT” 外部中断驱动文件）
 * 还修改了 /Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 中 173行的 HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
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
