#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *arg)
{
    printf("thread begin\n");
    sleep(3);
    printf("thread finish\n");
    return NULL;

}

int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 使用detach标记会等待线程完成之后回收相关资源 
    /**
     * int pthread_detach(pthread_t thread);
     * @brief 主线程不等待子线程终止 回收资源
     * @param thread: 线程ID
     * @return 0 - 成功  失败返回错误码
     */
    pthread_detach(tid);

    printf("父进程不能比子进程先结束 否则将强制杀死子进程\n");

    sleep(5);
    printf("main ending\n");
    return 0;
}
