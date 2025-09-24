#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

sem_t *full;
sem_t *empty;

int shardNum;

int rand_num(void)
{
    srand(time(NULL));
    return rand();
}
void * producer_thread(void *argv)
{
    for (int i = 0; i < 5; i++)
    {
        // 获取信号量
        sem_wait(empty);
        
        printf("\n第%d轮数据传输\n",i+1);
        sleep(1);
        shardNum = rand_num();

        // 释放信号量
        sem_post(full);
    }
    

}

void * consumer_thread(void *argv)
{
    for (size_t i = 0; i < 5; i++)
    {
        // 获取信号量
        sem_wait(full);
        printf("\n第%d轮开始读数据\n",i+1);
        sleep(1);
        printf("saved data [%d]\n",shardNum);
        sem_post(empty);
    }
    

}

int main(int argc, char const *argv[])
{
    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));

    //  初始化信号量
    sem_init(empty,0,1);
    sem_init(full,0,0);

    //创建生产者和消费者线程
    pthread_t producerTid, consumerTid;
    pthread_create(&producerTid,NULL,producer_thread,NULL);
    pthread_create(&consumerTid,NULL,consumer_thread,NULL);

    // 等待回收资源
    pthread_join(producerTid,NULL);
    pthread_join(consumerTid,NULL);

    // 销毁信号量
    sem_destroy(empty);
    sem_destroy(full);


    return 0;
}
