#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    // fork之前父进程单独运行
    int fd = open("io.txt",O_CREAT|O_WRONLY|O_APPEND,0644);
    
    if (-1 == fd)
    {
        perror("open io.txt failed");
        exit(EXIT_FAILURE);
        /* code */
    }

    /* 缓冲区存放写入的数据*/
    char buf[1024]; 

    pid_t pidNew = fork();

    // 父子进程资源共享
    if(0 > pidNew ) {
        close(fd);
        perror(" fork pidNew failed");
        exit(EXIT_FAILURE);
    } else if (0 == pidNew)
    {
        /* 子进程 */
        strcpy(buf,"子进程写入的数据\n");
    }else {
        /* 父进程 */
        sleep(1);
        strcpy(buf,"父进程写入的数据\n");
    }

    /* 父子进程并行 */
    ssize_t bytes_wr = write(fd,buf,strlen(buf));
    if(-1 == bytes_wr) {
        perror("Write buf failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (0 == pidNew) {
        printf("子进程写入完毕 并释放文件描述符\n");
    } else {
        printf("父进程写入完毕 并释放文件描述符\n");
    }

    close(fd);
    





    
    
    return 0;
}
