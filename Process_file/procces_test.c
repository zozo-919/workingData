#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int num = 0;
    pid_t newPid = fork();
    if (0 > newPid)
    {
        perror("create new pid failed");
        exit(1);
    } else if(0 == newPid) {
        num++;
        printf("child num = [%d]\n",num);
    } else {
        sleep(1);
        printf("father num = [%d]\n",num);

    }
    
    return 0;
}
