#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char shm_name[100] = {0};
    sprintf(shm_name,"/letter%d",getpid());
    int newFd = shm_open(shm_name, O_CREAT|O_RDWR, 0644);
    if(0 > newFd) {
        perror("shm_name");
        exit(1);
    }

    while (1)
    {
    }
    
    
    return 0;
}
