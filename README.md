# workingData

```mermaid
flowchart LR
    A[Ŀ¼] --> B[���������] --> C[BasisComputer/] 
    A --> D[C����] --> E[C/]
    A --> F[C++����] --> G[C++/]
    A --> H[���ݽṹ] --> I[Data_structure/] 
        I --> 1[linklist/  -- ����]
        I --> 2[sqlist/  -- ˳��� ]
        I --> 3[Queue/  -- ���� ]
            3 --> 7[Sequeue/  -- ˳�����]
            3 --> 8[Listqueue/ -- ��ʽ����]
        I --> 4[Ballclock -- �������� ]
        I --> 5[Stack --  ջ]
            5 --> 9[Liststack -- ˳��ջ]
            5 --> 10[Sqstack -- ��ʽջ]
        I --> 6[Tree/ ��]

    A --> J[FreeRTOS����ϵͳ] --> K[FreeRTOS/]
        K --> 11[Delay_function -- ��ʱ������ʾ]
        K --> 12[dynamicTaskCreateFunc/ -- ��̬����������]
        K --> 13[Event_flag_group/ �¼���־��]
        K --> 14[freertos-demo/ ����ģ��]
        K --> 15[freertosfile/ �����ļ��ṹ]
        K --> 16[Insertion_and_delection_of_list_items/ �б���Ĳ�����ɾ��]
        K --> 17[IRQ/ �жϹ���]
        K --> 18[ISRmanageFunc/ �жϹ���]
        K --> 19[Low-power_Tickless/ �͹���Ticklessģʽ]
        K --> 20[Memory_Management/ �ڴ����]
        K --> 21[Query_of_task_status/ ����״̬��ѯ]
        K --> 22[Queue_operations/ ���м�����]
        K --> 23[Queue_set_operation/ ���в���]
        K --> 24[semaphore/ �ź���]
        K --> 25[staticTaskCreateFunc/ ��̬����������]
        K --> 26[Task_execution_time_statistics/ ��������ʱ��ͳ��API]
        K --> 27[task_notification/ ����֪ͨ]
            27 --> 151[Task_notification_simulation_counting_semaphore ����֪ͨģ��������ź���]
            27 --> 152[Task_notification_simulation_Event_Flag_Group ����֪ͨģ���¼���־��]
            27 --> 153[Task_notification_simulation_Message_Inbox ����֪ͨģ����Ϣ����]
            27 --> 154[Task_notification_simulation_of_binary_semaphore ����֪ͨģ���ֵ�ź���]
        K --> 28[taskSuspendResumeFunc/ �������ָ�����]
        K --> 29[Time_slice_scheduling/ ʱ��Ƭ����]
        K --> 150[software_timer/ �����ʱ��]

    A --> L[�ļ�IO/��׼IO] --> M[IO_file/]
        M --> 30[Dynamic_library_test/ ��̬��]
        M --> 31[Static_library_test/ ��̬��]
        M --> 32[fclose_test.c  fclose����]
        M --> 33[fgetc_test.c  fgetc����]
        M --> 34[fgets_test.c  fgets����]
        M --> 35[fopen_test.c  fopen����]
        M --> 36[fprintf_test.c fprintf����]
        M --> 37[fputc_test.c  fputc����]
        M --> 38[fputs_test.c  fputs����]
        M --> 39[fread_test.c  fread����]
        M --> 40[fscanf_test.c  fscanf����]
        M --> 41[fwrite_test.c  fwrite����]
        M --> 42[stdin_out_err_test.c ��׼����/���/����]
        M --> 43[system_call_test.c  read/write/close����]
        M --> 44[unistd_test.c open����]

    A --> N[������] --> O[Network_programming/]
        O --> 45[udp_client.c udp_server.c  udpͨ��]
        O --> 46[single_conn_client.c single_conn_server.c ]
        O --> 47[num_endianess_convert.c]
        O --> 48[multi_conn_threads_client.c multi_conn_threads_server.c]
        O --> 49[multi_conn_processes_client.c multi_conn_processes_server.c ]
        O --> 50[inet_endian_convert.c  ������ֽ���ת��]
        O --> 51[epoll/]
        51 --> 52[epoll_test.c  ��·���÷����]
        O --> 53[deamon_and_multiplex/]
        53 --> 54[tcp_client.c tcp_server.c �ػ�����]
        53 --> 55[daemon_test.c �ػ�����]


    A --> P[����] --> Q[Process_file/]
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

    A --> R[�߳�] --> S[Thread_file/]
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

    A --> T[����/�̰߳�ȫ] --> U[process_thread_theory/] --> 91[virtual_memory_test.c]

    A --> V[STM32ѧϰ ] --> W[STM32/]
        W --> 92[stm32_examples/]
        92 --> 93[IIC/] 
            93 --> 160[EEPROM/ ģ������]
        
        92 --> 94[Uart/]
            94 --> 161[showOfTheFunctionOf_uart/ ������ʾ���� ]
            94 --> 162[uart_send/   ���ڷ���]
            94 --> 163[uart_recv/   ���ڽ���]
            94 --> 164[uart_recv ISR/ ���ڽ��� �ж�]
            94 --> 165[uart_recv_dataPacket ISR/ ���ڽ������ݰ��ж�]

        92 --> 95[GPIO/]
            95 --> 166[relay_module/    �̵���ģ��]
            95 --> 167[Led/ ���]
            95 --> 168[button_control_led/  ��������led]
            95 --> 169[Buzzer_module/   ������ģ��]
            95 --> 170[Key-controlled_buzzer_module/    �������Ʒ�����ģ��]

        92 --> 96[ADC/]
            96 -->171[Demonstration_of_ADC_Function/   ģ������ת����������ʾ]
            96 -->172[Single_channel_acquistion_experiment_of_ADC   ģ������ת�����ĵ�ͨ���ɼ�ʵ��]
        
        92 --> 97[DMA/]
            97 --> 173[Demonstration_of_DMA_Function unused DMA/  DMA������ʾ-û����DMA]
            97 --> 174[Demonstration_of_DMA_Function used DMA/  DMA������ʾ-����DMA]
            97 --> 175[DMA_transfer M_to_M/ DMA���ݴ���-�Ĵ������Ĵ���]
            97 --> 176[DMA_transfer M_to_Pdevice/ DMA���ݴ���-�Ĵ���������]

        92 --> 98[ISR/]
            98 --> 177[ISR_handle/ �жϽ������� ]
            98 --> 178[ISR_exter_application/    �ⲿ�ж�Ӧ��]
            98 --> 179[ISR_priority/ �ж����ȼ���ʾ]
            
        92 --> 99[HAL/  HAL����ֲ]
    
    A --> X[Makefileѧϰ] --> Y[Makefile_Learning/]
    A --> Z[Markdownѧϰ] --> a[Markdown_manual/]
    A --> b[QT/]
    A --> c[�����ʼ�] --> d[workRecord/]
    A --> e[���߼�] --> f[Tools/]
        f --> 100[GCC/]
        f --> 101[git/]
        f --> 102[JLINK/]
        f --> 103[Keil_manual/]
        f --> 104[tar_zip_7z/  �ļ���ѹ����ѹ]
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


### ���������
* ==**BasisComputer/**==

### C����ѧϰ
* ==**C/**==

### C++ѧϰ
* ==**C++/**==

### ���ݽṹ
* ==**Data_structure/**==
  * **linklist/   -- ����**
  * **sqlist/     -- ˳���**
  * **Queue/  -- ����**
    * ***Sequeue/  -- ˳�����***
    * ***Listqueue/ -- ��ʽ����***
  * **Ballclock -- ��������**
  * **Stack --  ջ**
    *  ***Liststack -- ˳��ջ***
    *  ***Sqstack -- ��ʽջ***
  * **Tree/ ��**

### FreeRTOS����ϵͳ
* ==**FreeRTOS/**==
  * **Delay_function -- ��ʱ����**
  * **dynamicTaskCreateFunc/  --  ��̬����������**
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

### �ļ�/��׼IO
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

### ������
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

### ����
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

### �߳�
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


### ����/�̰߳�ȫ
* ==**process_thread_theory/**==
  * **virtual_memory_test.c**

### STM32 ѧϰ��STM32F103C8 Ϊ����
* ==**STM32/**==
  * stm32_examples/
    * IIC/
    * Uart/
    * GPIO/
    * ADC/
    * DMA/
    * IRQ
    * HAL/

### Makefileѧϰ
* ==**Makefile_Learning/**==

### Markdown ѧϰ�ֲ�
* ==**Markdown_manual/**==

### QT ѧϰ
* ==**QT**==

### ���߼�
* ==**Tools/**==
  * **GCC/**
  * **git/**
  * **JLINK/**
  * **Keil_manual/**
  * **tar_zip_7z/**
  * **XCOM/**
  * **xshell/**
  * **Xtfp/**

### �����ʼ�?
* **workRecord/**