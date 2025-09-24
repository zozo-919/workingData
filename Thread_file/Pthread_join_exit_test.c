#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


// 一个进程的多个线程同时使用到标准输入输出 将造成冲突问题 导致只有一个线程使用到标准输入输出

// 定义一个结构体 来接收线程结果
typedef struct Res{
    char *p;
    int len;
}Res;

void * red_thread(void *args)
{
    // 参数解析
    char code = *((char*)args);
    // 初始化res结构体
    Res *rRes = malloc(sizeof(Res));
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans,100,stdin);
        if(ans[0] == code) {
            free(ans);
            printf("red received and red_leaving\n");
            /**
             * #include <string.h>
             * char *strdup(const char *s);
             * @brief 复制字符串 该函数会分配足够的内存来存储输入的字符串s的副本 然后将s的内容复制到新分配的内存中 最后返回指向新字符串的指针
             * @param s: 要复制的源字符串 以\0结尾
             * @return 返回指向新分配的字符串的指针 失败NULL  这个内存不用了必须释放
             */
            char *redans = strdup("red go to paris\n");
            rRes->p = redans;
            rRes->len = strlen(redans);

            //结束线程 返回结果
            /**
             * void pthread_exit(void *retval);
             * @brief 结束关闭调用该方法的线程 并返回一个内存指针用于存放结果
             * @param retval: 要返回给其他线程的数据
             */
            pthread_exit((void*)rRes);
        } else {
            printf("red still here....\n");
        }
    }
}

void * white_thread(void *args)
{
    char code = *((char*)args);
    char *ans = malloc(101);
    Res *wRes = malloc(sizeof(Res));
    while (1)
    {
        fgets(ans,100,stdin);
        if(ans[0] == code) {
            free(ans);
            printf("white received and white_leaving\n");
            char *whiteans = strdup("white go to China\n");
            wRes->p = whiteans;
            wRes->len = strlen(whiteans);

            /** 
             * 结束线程 返回结果  
             * wRes这个结果将作为返回值传递给pthread_join的第二个参数接收 
             * 也就是本例中的w_res
             */
            pthread_exit((void*)wRes);
        } else {
            printf("white still here....\n");
        }
    }

}

int main(int argc, char const *argv[])
{
    pthread_t redPid;
    pthread_t whitePid;

    char r_arg1 = 'r';
    char w_arg2 = 'w';

    Res * r_res = NULL;
    Res * w_res = NULL;

    // 线程创建
    pthread_create(&redPid,NULL,red_thread,&r_arg1);
    pthread_create(&whitePid,NULL,white_thread,&w_arg2);

    pthread_join(redPid,(void**)&r_res);
    printf("red [%d] ending is:%s",r_res->len,r_res->p);
    free(r_res->p);
    free(r_res);

    pthread_join(whitePid,(void**)&w_res);
    printf("white [%d] ending is:%s",w_res->len,w_res->p);
    free(w_res->p);  // 这里释放的就是由strdup分配的内存
    free(w_res);

    return 0;
}
