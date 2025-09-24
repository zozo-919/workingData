#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 程序实现创建两个线程 1.读取控制台信息 写入到缓存中 2.将缓存信息写出到控制台 */

#define BUF_LEN 1024
char *buf;

// 线程一: 从控制台读数据 并写入buf
void *input_thread(void *argv) 
{
    int i = 0;
    while (1)
    {
        char c = fgetc(stdin);
        if(c && c!='\n') {
            buf[i] = c;
            i++;
            // buf[i++] = c;
        }
        // 缓冲区索引溢出
        if(i >= BUF_LEN) {
            i = 0;
        }
    }
    
}

// 线程二: 从buf中读数据 打印到控制台
void *output_thread(void *argv)
{
    int i = 0;
    while (1)
    {
        // 读取一个字节 并写出到控制台
        if (buf[i]) {
            fputc(buf[i],stdout);
            fputc('\n',stdout);
            buf[i] = 0;
            i++;
            // 读取数据到最大下表
            if(i >= BUF_LEN) {
                i = 0;
            }
        } else {
            sleep(1);
        }
    }
    

}

int main(int argc, char const *argv[])
{
    // 声明线程id
    pthread_t pid_input;
    pthread_t pid_output;

    buf = malloc(BUF_LEN);
    memset(buf, 0, BUF_LEN);

    // 创建读线程
    /**
     * typedef unsigned long int pthread_t;
     * int pthread_create(pthread_t *thread,const pthread_attr_t *attr, void *(*start_routine)(void *), void * arg);
     * @brief 创建一个新的线程
     * @param thread: 指向线程标识符的指针 线程创建成功时 用于存储新创建线程的线程标识符
     *        attr:   一般传入NULL 线程采用默认属性  pthread_attr_t该结构体可以设置线程属性 如优先级、栈大小
     *        start_routine: 一个指向函数的指针 定义了新线程开始执行时的入口点 该函数必须接受一个void*类型的参数 并返回void*类型的结果
     *        arg: start_routine函数的参数 可以是一个指向任意类型数据的指针
     * @return 线程创建结果  0 - 成功 非0 - 失败
     */
    pthread_create(&pid_input,NULL,input_thread,NULL);
    
    // 创建写线程
    pthread_create(&pid_output,NULL,output_thread,NULL);

    // 主线程等待读写线程结束
    /**
     * int pthread_join(pthread_t thread, void **retval);
     * @brief 等待指定线程结束 获取目标线程的返回值 并在目标线程结束后回收它的资源
     * @param thread: 指定线程ID  retval: 这是一个可选参数 用于接收线程结束后传递的返回值 若非空则会在成功时 将线程的exit status复制到*retval所指向的内存位置 如果线程没有显式地通过pthread_exit提供返回值 则该参数将被设null或忽略
     * @return 0 - 成功  1 - 失败
     */
    pthread_join(pid_input,NULL);
    pthread_join(pid_output,NULL);

    free(buf);

    return 0;
}

