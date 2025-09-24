#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *arg)
{
    printf("thread begin\n");
    printf("working.............\n");
    sleep(2);
    // 创建线程取消点
    /**
     * #include <pthread.h>
     * void pthread_testcancel(void);
     * @brief 创建取消点：该函数在调用处创建一个线程取消点
     *        检查取消请求：如果线程收到了取消请求（pthread_cancel） 且线程的取消状态和类型允许取消 则线程会在该点终止
     *        无取消请求时：如果没有待处理的取消请求 函数立即返回 不产生其他效果
     */
    pthread_testcancel();
    printf("after cancel\n");
    return NULL;

}

int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 取消子线程
    /**
     * int pthread_cancel(pthread_t thread);
     * @brief 向目标线程发送取消请求 目标线程是否和何时响应取决于它的取消状态和类型
     *        取消状态：可以是enabled或disabled 如果取消状态为禁用 则取消请求会被挂起 直至线程启用取消功能 如果取消状态为启用 则线程的取消类型决定它何时取消
     *        取消类型：可以是asynchronous异步或deferred被推迟（默认值）
     *        asynchornous:意味着线程可能在任何时候被取消（通常立即被取消 但系统并不保证这一点）
     *        deferred: 被推迟意味着取消请求会被挂起 直至被取消的线程执行取消点函数时才会真正执行线程的取消操作
     *        取消点函数: 是在POSIX线程库中专门设计用于检查和处理取消请求的函数 当被取消的线程执行这些函数时 如果线程的取消状态时enabled且类型是deferred 则会立即响应取消请求并终止执行
     * @param thread: 目标线程 即被取消的线程
     * @return 成功返回 0 失败返回错误
     *  取消操作和pthread_cancel函数的调用是异步的 这个函数的返回值只能告诉调用者取消请求是否成功发送
     *  当线程被成功取消后 通过pthread_join和线程关联将会获得PTHREAD_CANCELED作为返回信息 
     *  这是判断取消释放完成的唯一方式
     */                  
    if(0 != pthread_cancel(tid)) {
        perror("pthread_cancel");
    }

    void *res;
    pthread_join(tid,&res);

    if(res == PTHREAD_CANCELED) {
        printf("cancel thread\n");
    } else {
        printf("thread still not cancel, exit code[%d]\n",*((int*)res));
    }

    return 0;
}
