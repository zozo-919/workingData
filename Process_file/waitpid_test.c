#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    //fork之前
    printf("no fork child\n");
    int subprocess_status;
    
    pid_t childPid = fork();
    if (0 > childPid)
    {
        perror("creat childPid failed");
        return 1;
    } else if(0 == childPid) {
        printf("creat child success\n");
        char *args[] ={"/sbin/ping","-c","10","www.baidu.com",NULL};
        char *envs[] = {NULL};
        printf("[%d] will execute command\n",getpid());
        int res = execve(args[0],args,envs);
        if( 0 > res) {
            return 1;
        }
    } else {
        printf("[%d]wait for chiled[%d]\n",getpid(),childPid);

        /**
         * pid_t waitpid(pid_t pid, int *wstatus, int options) 
         * @brief   等待子进程 回收子进程的状态 避免出现僵尸进程和孤儿进程
         * @param   pid: 进程id号
         *              （1）<-1 如-1*pgid，则等待进程组ID等于pgid的所有进程终止
         *              （2）=-1 等待任何子进程终止 并返回最先终止那个子进程的进程ID 儿孙都算
         *              （3）=0  等待同一进程组中任何子进程终止（但不包括组领导进程）只算儿子
         *              （4）>0  大于0仅等待指定进程ID的子进程终止
         *          wstatus: 子进程返回的状态码
         *          options: （1）WNOHANG 若无子进程终止 也立即返回 用于查看子进程状态而非等待
         *                   （2）WUNTRACED 收到子进程处于收到信号停止的状态 也返回
         *                   （3）WCONTINUED 如果通过发送SIGCONT 信号恢复了一个已停止的子进程 则也返回
         *                  一般情况下写0.
         * @return （1）成功等到子进程停止 返回pid
         *         （2）没等到并且没有设置WNOHANG 一直等
         *         （3）没等到设置WNOHANG 返回0
         *         （4）出错返回-1
         */
        waitpid(childPid,&subprocess_status,0);
    }

    printf("father wait child success\n");
    return 0;
}
