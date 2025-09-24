#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    // 调用fork之前 代码都在父进程中运行
    printf("父进程pid%d\n",getpid());

    // while (1);
    
    /**
     * pid_t fork(void)
     * @brief 使用fork创建子进程
     * @param 无
     * @return pid_t: int 进程号
     *              （1） -1:出错
     *              （2） 父进程中表示子进程的PID
     *               (3) 子进程中显示为0
     * 父子进程使用同一变量名pid 但两者pid保存在不同的内存空间 值也不一样 而不是同一变量自动改变了值
     */
    pid_t pid = fork();

    /**
     * 从fork之后 所有的代码都是在父子进程中各自执行一次 这里会打印两个值 一个是父进程中表示子进程的pid 一个是0
     */ 
    // printf("%d \n",pid);

    //  fork后得到的pid可以去区分父子进程
    if(pid < 0) {
        printf("fork 子进程失败\n");
    } else if (pid == 0) {
        // 执行单独子进程代码
        printf("Fork 子进程%d成功, 它的父进程是%d\n",getpid(),getppid());
    } else {
        //执行单独父进程代码
        printf("父进程%d进行中\n",getpid());
    }

    return 0;
}
