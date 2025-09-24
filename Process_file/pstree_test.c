#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    /* 跳转之前 */
    char * catName = "rourou";
    printf("I am %s, my num is[%d]\n",catName,getpid());

    /* 创建子进程 */
    pid_t dogPid = fork();
    if (0 > dogPid)
    {
        perror("dog come failed");
        exit(EXIT_FAILURE);
        /* code */
    } else if(0 == dogPid) {
        /* 子进程 dogCome 跳转*/
        char * dogName = "haha";
        char * args[] = {"/Users/zozo/Desktop/ForWorking/Process_file/execve",dogName,NULL};
        char * envs[] = {NULL};
        int ret = execve(args[0],args,envs);
        if(-1 == ret) {
            perror("my dog not come");
            exit(EXIT_FAILURE);
        }

        // 至此 子进程就跳转成功 
    } else {
        /* 父进程 继续*/
        printf(" my [%d] success welcom her child[%d]\n",getpid(),dogPid);

        // 永久挂起 等待输入任意一个字符停止
        char by = fgetc(stdin);
    }

    return 0;
}
