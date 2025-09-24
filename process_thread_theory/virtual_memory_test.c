#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int val = 123;
    pid_t pid = fork();
    if (0 > pid)
    {
        perror("fork fail");
        /* code */
    } else if (0 == pid)
    {
        /* code */
        val = 321;
        printf("子进程中val的值[%d] 地址值是%p\n",val,&val);
    } else {
        sleep(1);
        printf("父进程中val的值是[%d],地址是%p\n",val,&val);
    }
    
    
    return 0;
}
