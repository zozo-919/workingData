#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *arg)
{
    printf("thread begin\n");
    // 禁用取消
    /**
     * int pthread_setcancelstate(int state, int *oldstate);
     * @brief 设置调用线程的取消状态
     * @param state: 目标状态  oldstate: 指针 用于返回历史状态
     *          PTHREAD_CANCEL_DISABLE : 禁用取消功能
     *          PTHREAD_CANCEL_ENABLE: 启用取消功能
     * @return 成功返回0。失败返回非0错误码
     */
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    printf("pthread cancelstate is disable.............\n");

    /**
     * int pthread_setcanceltype(int type, int *oldtype);
     * @brief 设置调用线程的取消类型
     * @param type 目标类型。  oldtype: 指针 用于接收历史类型
     *          PTHREAD_CANCEL_ASYNCHRONOUS: 设置取消类型为异步
     *          PTHREAD_CANCEL_DEFERRED: 设置取消类型为推迟
     * @return 成功返回0 失败返回非零错误码
     */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    // 模拟工作
    printf("working ...\n");
    sleep(1);
    printf("after cancel\n");
    return NULL;

}

int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 取消子线程
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
