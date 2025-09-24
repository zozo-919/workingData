#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_writer(void *arg)
{
    // 写锁
    pthread_rwlock_wrlock(&rwlock);
    int tmp = shared_data+1;
    shared_data = tmp;
    printf("当前是%s 在写数据, shared_data为%d\n",(char*)arg,shared_data);
    pthread_rwlock_unlock(&rwlock);
}

void *lock_reader(void *args)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("当前是 %s 在读, shared_data[%d]\n",(char*)args,shared_data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
}

int main(int argc, char const *argv[])
{
    // 初始化 读写锁
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t writer1, writer2,reader1,reader2,reader3,reader4,reader5,reader6;

    pthread_create(&writer1,NULL,lock_writer,"writer1");

    pthread_create(&reader1,NULL,lock_reader,"reader1");
    pthread_create(&reader2,NULL,lock_reader,"reader2");
    pthread_create(&reader3,NULL,lock_reader,"reader3");

    pthread_create(&writer2,NULL,lock_writer,"writer2");

    pthread_create(&reader4,NULL,lock_reader,"reader4");
    pthread_create(&reader5,NULL,lock_reader,"reader5");
    pthread_create(&reader6,NULL,lock_reader,"reader6");


    // 主线程等待子线程运行 回收资源
    pthread_join(writer1,NULL);
    pthread_join(writer2,NULL);
    pthread_join(reader1,NULL);
    pthread_join(reader2,NULL);
    pthread_join(reader3,NULL);
    pthread_join(reader4,NULL);
    pthread_join(reader5,NULL);
    pthread_join(reader6,NULL);

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    
    return 0;
}
