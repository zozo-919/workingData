#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*********************** 本代码无法编译 macos系统不支持锁类型优先级 属性设置的函数  *************/
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
    // 创建读写锁属性对象
    pthread_rwlockattr_t rwAttr;
    pthread_rwlockattr_init(&rwAttr);
    
    // 修改参数设置写优先
    /**
     * #include <pthread.h>
     * int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *attr, int pref);
     * @brief 将attr指向的属性对象中的‘锁类型’属性设置为pref规定的值
     * @param attr 读写锁属性对象指针  
     *        pref：希望设置的锁类型 可以被设置为以下三种
     *              PTHREAD_RWLOCK_PREFER_READER_NP: 默认值 读线程优先
     *              PTHREAD_RWLOCK_PREFER_WRITER_NP: 写线程优先 但被glibc忽略
     *              PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP: 写线程优先 一般设为此值              
     * @return 0 - 成功  非0错误码 - 失败
     */
    pthread_rwlockattr_setkind_np(&rwAttr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    
    // 初始化 读写锁
    pthread_rwlock_init(&rwlock, &rwAttr);

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
