#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
#if 0
    /* main参数测试 */
    if (argc < 2)
    {
        printf("参数不够\n");
        return 1;

        /* code */
    }
    printf("I am %s, num%d\n",argv[1],getpid());

#else

    /* 跳转之前 */
    char *name = "haha";
    printf("my name is [%s] ,my num is[%d],暂未跳转\n",name,getpid());

    // 执行跳转
    /**
     * int execve(const char * __path, char * const __argv[], char * const __envp[]);
     * @brief   执行跳转
     * @param   __path:执行程序的路径     
     *          __argv[]: 传入的参数 -> 对应执行程序main方法的第二个参数
     *                  （1）：第一个参数固定是程序的名称 ->执行程序的路径
     *                  （2）：执行程序需要传入的参数
     *                  （3）：最后一个参数一定是NULL
     *          __envp[]: 传递的环境变量
     *                  （1）：环境变量参数: key=value
     *                  （2）：最后一个参数一定是NULL
     * @return 成功不返回 失败返回-1
     */

    char * argvs[] = {"/Users/zozo/Desktop/ForWorking/Process_file/execve",name,NULL};
    char * envs[] = {NULL};
    int ret = execve(argvs[0],argvs,envs);
    if(-1 == ret) {
        perror("execve failed");
        return 1;
    }

    // 此后的代码无意义 程序成功发生跳转
#endif

    return 0;
}
