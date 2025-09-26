# workingData

```mermaid
flowchart LR
    A[目录] --> B[计算机基础] --> C[BasisComputer/] 
    A --> D[C语言] --> E[C/]
    A --> F[C++语言] --> G[C++/]
    A --> H[数据结构] --> I[Data_structure/] 
        I --> 1[linklist/  -- 链表]
        I --> 2[sqlist/  -- 顺序表 ]
        I --> 3[Queue/  -- 队列 ]
            3 --> 7[Sequeue/  -- 顺序队列]
            3 --> 8[Listqueue/ -- 链式队列]
        I --> 4[Ballclock -- 球钟问题 ]
        I --> 5[Stack --  栈]
            5 --> 9[Liststack -- 顺序栈]
            5 --> 10[Sqstack -- 链式栈]
        I --> 6[Tree/ 树]

    A --> J[FreeRTOS操作系统] --> K[FreeRTOS/]
        K --> 11[Delay_function -- 延时函数演示]
        K --> 12[dynamicTaskCreateFunc/ -- 动态创建任务函数]
        K --> 13[Event_flag_group/ 事件标志组]
        K --> 14[freertos-demo/ 基本模板]
        K --> 15[freertosfile/ 基础文件结构]
        K --> 16[Insertion_and_delection_of_list_items/ 列表项的插入与删除]
        K --> 17[IRQ/ 中断管理]
        K --> 18[ISRmanageFunc/ 中断管理]
        K --> 19[Low-power_Tickless/ 低功耗Tickless模式]
        K --> 20[Memory_Management/ 内存管理]
        K --> 21[Query_of_task_status/ 任务状态查询]
        K --> 22[Queue_operations/ 队列集操作]
        K --> 23[Queue_set_operation/ 队列操作]
        K --> 24[semaphore/ 信号量]
        K --> 25[staticTaskCreateFunc/ 静态创建任务函数]
        K --> 26[Task_execution_time_statistics/ 任务运行时间统计API]
        K --> 27[task_notification/ 任务通知]
            27 --> 151[Task_notification_simulation_counting_semaphore 任务通知模拟计数型信号量]
            27 --> 152[Task_notification_simulation_Event_Flag_Group 任务通知模拟事件标志组]
            27 --> 153[Task_notification_simulation_Message_Inbox 任务通知模拟消息邮箱]
            27 --> 154[Task_notification_simulation_of_binary_semaphore 任务通知模拟二值信号量]
        K --> 28[taskSuspendResumeFunc/ 任务挂起恢复函数]
        K --> 29[Time_slice_scheduling/ 时间片调度]
        K --> 150[software_timer/ 软件定时器]

    A --> L[文件IO/标准IO] --> M[IO_file/]
        M --> 30[Dynamic_library_test/ 动态库]
        M --> 31[Static_library_test/ 静态库]
        M --> 32[fclose_test.c  fclose函数]
        M --> 33[fgetc_test.c  fgetc函数]
        M --> 34[fgets_test.c  fgets函数]
        M --> 35[fopen_test.c  fopen函数]
        M --> 36[fprintf_test.c fprintf函数]
        M --> 37[fputc_test.c  fputc函数]
        M --> 38[fputs_test.c  fputs函数]
        M --> 39[fread_test.c  fread函数]
        M --> 40[fscanf_test.c  fscanf函数]
        M --> 41[fwrite_test.c  fwrite函数]
        M --> 42[stdin_out_err_test.c 标准输入/输出/错误]
        M --> 43[system_call_test.c  read/write/close函数]
        M --> 44[unistd_test.c open函数]

    A --> N[网络编程] --> O[Network_programming/]
        O --> 45[udp_client.c udp_server.c  udp通信]
        O --> 46[single_conn_client.c single_conn_server.c ]
        O --> 47[num_endianess_convert.c]
        O --> 48[multi_conn_threads_client.c multi_conn_threads_server.c]
        O --> 49[multi_conn_processes_client.c multi_conn_processes_server.c ]
        O --> 50[inet_endian_convert.c  网络端字节序转换]
        O --> 51[epoll/]
        51 --> 52[epoll_test.c  多路复用服务端]
        O --> 53[deamon_and_multiplex/]
        53 --> 54[tcp_client.c tcp_server.c 守护进程]
        53 --> 55[daemon_test.c 守护进程]


    A --> P[进程] --> Q[Process_file/]
        Q --> 56[consumer_test.c ]
        Q --> 57[execve_test.c ]
        Q --> 58[fifo_read_test.c]
        Q --> 59[fifo_write_test.c ]
        Q --> 60[fork_execve_test.c ]
        Q --> 61[fork_fd_test.c ]
        Q --> 62[fork_test.c ]
        Q --> 63[parent_child_mq_test.c ]
        Q --> 64[procces_test.c ]
        Q --> 65[producer_test.c ]
        Q --> 66[pstree_test.c ]
        Q --> 67[shared_memory_block.c ]
        Q --> 68[shared_memory.c]
        Q --> 69[signal_test.c ]
        Q --> 70[system_test.c ]
        Q --> 71[unnamed_pipe_test.c ]
        Q --> 72[waitpid_test.c ]

    A --> R[线程] --> S[Thread_file/]
        S --> 73[named_sem_bin.c ]
        S --> 74[pthread_cancel_async_test.c ]
        S --> 75[pthread_cancel_diable_test.c]
        S --> 76[pthread_cancel_test.c ]
        S --> 77[pthread_detach_test.c]
        S --> 78[pthread_join_exit_test.c]
        S --> 79[pthread_lock_condition_var.c]
        S --> 80[race_condition_test.c]
        S --> 81[rwlock_test.c]
        S --> 82[rwlock_write_hungry_solved.c]
        S --> 83[rwlock_write_hungry_test.c]
        S --> 84[rwlock_write_unlock_test.c]
        S --> 85[Thread_create_test.c ]
        S --> 86[thread_pool_test.c ]
        S --> 87[unnamed_sem_bin_process.c]
        S --> 88[unnamed_sem_bin_thread.c]
        S --> 89[unnamed_sem_count_process.c]
        S --> 90[unnamed_sem_count_thread.c]

    A --> T[进程/线程安全] --> U[process_thread_theory/] --> 91[virtual_memory_test.c]

    A --> V[STM32学习 ] --> W[STM32/]
        W --> 92[stm32_examples/]
        92 --> 93[IIC/] 
            93 --> 160[EEPROM/ 模块运用]
        
        92 --> 94[Uart/]
            94 --> 161[showOfTheFunctionOf_uart/ 串口演示函数 ]
            94 --> 162[uart_send/   串口发送]
            94 --> 163[uart_recv/   串口接收]
            94 --> 164[uart_recv ISR/ 串口接收 中断]
            94 --> 165[uart_recv_dataPacket ISR/ 串口接收数据包中断]

        92 --> 95[GPIO/]
            95 --> 166[relay_module/    继电器模块]
            95 --> 167[Led/ 点灯]
            95 --> 168[button_control_led/  按键控制led]
            95 --> 169[Buzzer_module/   蜂鸣器模块]
            95 --> 170[Key-controlled_buzzer_module/    按键控制蜂鸣器模块]

        92 --> 96[ADC/]
            96 -->171[Demonstration_of_ADC_Function/   模拟数字转换器功能演示]
            96 -->172[Single_channel_acquistion_experiment_of_ADC   模拟数字转换器的单通道采集实验]
        
        92 --> 97[DMA/]
            97 --> 173[Demonstration_of_DMA_Function unused DMA/  DMA功能演示-没启用DMA]
            97 --> 174[Demonstration_of_DMA_Function used DMA/  DMA功能演示-启用DMA]
            97 --> 175[DMA_transfer M_to_M/ DMA数据传输-寄存器到寄存器]
            97 --> 176[DMA_transfer M_to_Pdevice/ DMA数据传输-寄存器到外设]

        92 --> 98[ISR/]
            98 --> 177[ISR_handle/ 中断紧急处理 ]
            98 --> 178[ISR_exter_application/    外部中断应用]
            98 --> 179[ISR_priority/ 中断优先级演示]
            
        92 --> 99[HAL/  HAL库移植]
    
    A --> X[Makefile学习] --> Y[Makefile_Learning/]
    A --> Z[Markdown学习] --> a[Markdown_manual/]
    A --> b[QT/]
    A --> c[工作笔记] --> d[workRecord/]
    A --> e[工具集] --> f[Tools/]
        f --> 100[GCC/]
        f --> 101[git/]
        f --> 102[JLINK/]
        f --> 103[Keil_manual/]
        f --> 104[tar_zip_7z/  文件的压缩解压]
        f --> 105[XCOM/]
        f --> 106[xshell/]
        f --> 107[Xtfp/]

        style A fill:#ca5ea0, color:#FFFF
        style B fill:#afafff, color:#333
        style C fill:#afafff, color:#333
        style D fill:#f9ca24, color:#333
        style E fill:#f9ca24, color:#333
        style F fill:#81eff1, color:#333
        style G fill:#81eff1, color:#333
        style H fill:#ff9fb3, color:#333
        style I fill:#ff9fb3, color:#333
        style J fill:#e3eaa7, color:#333
        style K fill:#e3eaa7, color:#333
        style L fill:#7bed9f, color:#333
        style M fill:#7bed9f, color:#333
        style N fill:#7bb291, color:#333
        style O fill:#7bb291, color:#333
        style P fill:#fad07e, color:#333
        style Q fill:#fad07e, color:#333
        style R fill:#38f9d7, color:#333
        style S fill:#38f9d7, color:#333
        style T fill:#81eff1, color:#333
        style U fill:#81eff1, color:#333
        style V fill:#7bed9f, color:#333
        style W fill:#7bed9f, color:#333
        style X fill:#7bb291, color:#333
        style Y fill:#7bb291, color:#333
        style Z fill:#e3eaa7, color:#333
        style a fill:#e3eaa7, color:#333
        style b fill:#ff9fb3, color:#333
        style c fill:#f8da10, color:#333
        style d fill:#f8da10, color:#333
        style e fill:#afafff, color:#333
        style f fill:#afafff, color:#333

```


### 计算机基础
* ==**BasisComputer/**==

### C语言学习
* ==**C/**==

### C++学习
* ==**C++/**==

### 数据结构
* ==**Data_structure/**==
  * **linklist/   -- 链表**
  * **sqlist/     -- 顺序表**
  * **Queue/  -- 队列**
    * ***Sequeue/  -- 顺序队列***
    * ***Listqueue/ -- 链式队列***
  * **Ballclock -- 球钟问题**
  * **Stack --  栈**
    *  ***Liststack -- 顺序栈***
    *  ***Sqstack -- 链式栈***
  * **Tree/ 树**

### FreeRTOS操作系统
* ==**FreeRTOS/**==
  * **Delay_function -- 延时函数**
  * **dynamicTaskCreateFunc/  --  动态创建任务函数**
  * **Event_flag_group/**
  * freertos-demo/
  * freertosfile/
  * Insertion_and_delection_of_list_items/
  * IRQ/
  * ISRmanageFunc/
  * Low-power_Tickless/
  * Memory_Management/
  * Query_of_task_status/
  * Queue_operations/
  * Queue_set_operation/
  * semaphore/
  * staticTaskCreateFunc/
  * Task_execution_time_statistics/
  * task_notification/
  * taskSuspendResumeFunc/
  * Time_slice_scheduling/

### 文件/标准IO
* ==**IO_file/**==
  * **Dynamic_library_test/**
  * Static_library_test/
  * fclose_test.c
  * fgetc_test.c
  * fgets_test.c
  * fopen_test.c
  * fprintf_test.c
  * fputc_test.c
  * fputs_test.c
  * fread_test.c
  * fscanf_test.c
  * fwrite_test.c
  * stdin_out_err_test.c
  * system_call_test.c
  * unistd_test.c

### 网络编程
* ==**Network_programming**==
  * **udp_client.c udp_server.c**
  * **single_conn_client.c single_conn_server.c**
  * **num_endianess_convert.c**
  * **multi_conn_threads_client.c multi_conn_threads_server.c**
  * **multi_conn_processes_client.c multi_conn_processes_server.c**
  * **inet_endian_convert.c**
  * **epoll/**
    * **epoll_test.c**
  * **deamon_and_multiplex/**
    * **tcp_client.c tcp_server.c**
    * **daemon_test.c**

### 进程
* ==**Process_file/**==
  * **consumer_test.c**
  * **execve_test.c**
  * **fifo_read_test.c**
  * **fifo_write_test.c**
  * **fork_execve_test.c**
  * **fork_fd_test.c**
  * **fork_test.c**
  * **parent_child_mq_test.c**
  * **procces_test.c**
  * **producer_test.c**
  * **pstree_test.c**
  * **shared_memory_block.c**
  * **shared_memory.c**
  * **signal_test.c**
  * **system_test.c**
  * **unnamed_pipe_test.c**
  * **waitpid_test.c**

### 线程
* ==**Thread_file/**==
  * **named_sem_bin.c**
  * **pthread_cancel_async_test.c**
  * **pthread_cancel_diable_test.c**
  * **pthread_cancel_test.c**
  * **pthread_detach_test.c**
  * **pthread_join_exit_test.c**
  * **pthread_lock_condition_var.c**
  * **race_condition_test.c**
  * **rwlock_test.c**
  * **rwlock_write_hungry_solved.c**
  * **rwlock_write_hungry_test.c**
  * **rwlock_write_unlock_test.c**
  * **Thread_create_test.c**
  * **thread_pool_test.c**
  * **unnamed_sem_bin_process.c**
  * **unnamed_sem_bin_thread.c**
  * **unnamed_sem_count_process.c**
  * **unnamed_sem_count_thread.c**


### 进程/线程安全
* ==**process_thread_theory/**==
  * **virtual_memory_test.c**

### STM32 学习（STM32F103C8 为例）
* ==**STM32/**==
  * stm32_examples/
    * IIC/
    * Uart/
    * GPIO/
    * ADC/
    * DMA/
    * IRQ
    * HAL/

### Makefile学习
* ==**Makefile_Learning/**==

### Markdown 学习手册
* ==**Markdown_manual/**==

### QT 学习
* ==**QT**==

### 工具集
* ==**Tools/**==
  * **GCC/**
  * **git/**
  * **JLINK/**
  * **Keil_manual/**
  * **tar_zip_7z/**
  * **XCOM/**
  * **xshell/**
  * **Xtfp/**

### 工作笔记?
* **workRecord/**