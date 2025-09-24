#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *arg)
{
    printf("thread begin\n");
    
    // 设置取消类型为异步
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    printf("working.............\n");
    
    int i = 0;
    while (1) {
        // sleep(1);
        printf("%d\n",i++);
        // usleep(5);

    }
    
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
