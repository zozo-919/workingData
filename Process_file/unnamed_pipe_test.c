#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 将程序传递进来的第一个命令行参数 传输给子进程
    if(argc != 2) {
        perror("argc != 2");
        exit(1);
    }

    // 创建管道
    int pipefd[2] = {0};
    /**
     * int pipe(int pipefd[2]);
     * @brief 创建匿名管道 （内核之中 单向通信）
     * @param pipefd: 用于返回指向管道两端的两个文件描述符 
     *          pipefd[0]: 指向管道的读端
     *          pipefd[1]: 指向管道的写端
     * @return  0 -成功     -1 -失败
     */
    int res = pipe(pipefd);
    if(res == -1) {
        perror("create pipe failed");
        exit(1);
    }

    pid_t newPid = fork();
    if(0 > newPid) {
        perror("fork new pid failed");
        exit(EXIT_FAILURE);
    }

    if (0 == newPid)
    {
        /* 子进程 读取管道数据 打印到控制台 */
        close(pipefd[1]);
        char buf;

        char *str = "begin to write data : ";
        write(STDOUT_FILENO, str, strlen(str));

        /* 读数据 并写到控制台 */
        while (read(pipefd[0],&buf,1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO,"\n",1);
        
        close(pipefd[0]);
        exit(0);

    } else {
        /* 父进程 写入管道数据 提供给子进程读*/
        // 关闭读端
        close(pipefd[0]);
        // 将数据写入到管道中
        printf("[%d] write message\n",getpid());
        write(pipefd[1],argv[1],strlen(argv[1]));
        close(pipefd[1]);
        waitpid(newPid, NULL, 0);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
