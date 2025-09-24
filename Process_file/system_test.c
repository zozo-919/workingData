#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    /**
     * int system(const char * __command);
     * @brief 使用标准库函数创建子进程
     * @param   __command: 使用linux命令直接创建一个子进程
     * @return  成功返回0 失败返回失败编号 
     */
    int sysRes = system("ping -c 10 www.baidu.com");  // ping 10次 baidu.com
    if(0 != sysRes)
    {
        perror("system ");
        exit(EXIT_FAILURE);
    }
    
    
    return 0;
}
