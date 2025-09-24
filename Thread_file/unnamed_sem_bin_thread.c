#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include <semaphore.h>
#include </Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/semaphore.h>

int shardNum = 0 ;

sem_t unnamedSem;

void *plus_one(void *args)
{
    // 等待信号量
    /**
     * #include <semaphore.h>
     * int sem_wait(sem_t *sem)
     * @brief 相当于加锁
     * @param sem: 指向信号量对象的指针
     * @return 0 - 成功  -1 - 失败
     */
    sem_wait(&unnamedSem);
    
    int tmp = shardNum +1;
    shardNum = tmp;

    // 释放信号量 相当于解锁
    /**
     * #include <semaphore.h>
     * int sem_post(sem_t *sem)
     * @brief 唤醒因等待sem而阻塞的信号量 相当于解锁 
     * @param sem: 指向信号量对象的指针
     * @return 0 - 成功  -1 - 失败
     */
    sem_post(&unnamedSem);
}


int main(int argc, char const *argv[])
{
    // 初始化信号量
    /**
     * int sem_init(sem_t * _sem, int _pshared, unsigned int _value);
     * @brief 信号量初始化
     * @param  _sem: 信号量的地址   _pshared: 使用方式 0线程间通信 1进程间通信  _value: 初始值
     * @return 0 - 成功  -1 - 失败
     * 
     */
    int initRes = sem_init(&unnamedSem,0,1);
    if(0 != initRes) {
        perror("sem init ");
        return 1;
    }

    pthread_t tid[10000];
    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i,NULL,plus_one,NULL);
    }
    
    for (int i = 0; i < 10000; i++) {
        pthread_join(tid[i],NULL);
    }
    
    printf("shardnum = %d\n",shardNum);

    // 销毁信号量
    /**
     * int sem_destroy(sem_t * sem);
     * @brief  用于销毁通过sem_init初始化的未命名信号量
     * @param sem:  已初始化的未命名信号量
     * @return 0 - 成功  -1 - 失败
     */
    int desRes = sem_destroy(&unnamedSem);
    if(0 != desRes) {
        perror("sem destroy");
    }
    

    return 0;
}
