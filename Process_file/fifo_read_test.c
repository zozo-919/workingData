#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char const *argv[])
{

    /**
     * int mkfifo(const char *pathname, mode_t mode);
     * @brief 创建有名管道 创建一个路径为pathname的FIFO专用文件 权限为mode
     * @param pathname： 有名管道绑定的文件路径  mode：有名管道绑定的文件权限
     * @return 0-成功
     */
    char *fifo_path = "/tmp/myfifo";

    // 对有名管道的特殊文件 创建fd
    int newfd = open(fifo_path,O_RDONLY);
    if(newfd == -1) {
        perror("OPEN FILE FAILED");
        exit(1);
    }

    char buf[100];
    ssize_t read_num;

    // 读管道信息
    while((read_num = read(newfd,buf,100)) > 0)
    {
        // 将读到的信息输出到控制台
        write(STDOUT_FILENO, buf, read_num);
    }

    if(read_num < 0){
        perror("read");
        close(newfd);
        exit(1);
    }

    printf("save data finished process ending\n");
    close(newfd);

    return 0;
}