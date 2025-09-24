#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buf[BUFFER_SIZE];
int cnt = 0;

// 初始化互斥锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * producer_thread(void * args)
{
    // 向buf中写数据
    int item =1;

    pthread_mutex_lock(&mutex);

    while (1)
    {
        // pthread_mutex_lock(&mutex);

        // 当缓冲区写满 则使用条件变量来暂停当前线程
        if(cnt == BUFFER_SIZE) {
            item = 1;
            // 唤醒另一个线程
            pthread_cond_signal(&cond);
            // 暂停线程 
            pthread_cond_wait(&cond, &mutex);
        }

        // 缓冲区还可以写
        buf[cnt++] = item++;
        printf("write num [%d]\n",buf[cnt-1]);

        // // 唤醒另一个线程
        // pthread_cond_signal(&cond);

        // pthread_mutex_unlock(&mutex);
    }

        pthread_mutex_unlock(&mutex);

    

}

void * consumer_thread(void *args)
{
    // 从buf中读数据
    pthread_mutex_lock(&mutex);

    while (1)
    {
        // pthread_mutex_lock(&mutex);
        if(0 == cnt) {
            // 通知写线程可以继续写 换线写线程
            pthread_cond_signal(&cond);

            // 线程中无数据可读 暂停线程
            pthread_cond_wait(&cond,&mutex);
        }

        printf("read num [ %d]\n",buf[--cnt]);

        // 唤醒另一个线程
        pthread_cond_signal(&cond);
        
        // pthread_mutex_unlock(&mutex);

    }

    pthread_mutex_unlock(&mutex);

    

}

int main(int argc, char const *argv[])
{
    // 创建两个线程 一个向buf中写 一个从buf中读
    pthread_t producerPid, consumerPid;
    pthread_create(&producerPid,NULL,producer_thread,NULL);
    pthread_create(&consumerPid,NULL,consumer_thread,NULL);


    // 主线程等待回收子线程资源
    pthread_join(producerPid,NULL);
    pthread_join(consumerPid,NULL);

    return 0;
}
