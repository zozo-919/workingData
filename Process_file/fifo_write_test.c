#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char const *argv[])
{

    /**
     * int mkfifo(const char *pathname, mode_t mode);
     * @brief 创建有名管道 创建一个路径为pathname的FIFO专用文件 权限为mode 有名管道可用于任何进程间的通信
     * @param pathname： 有名管道绑定的文件路径  mode：有名管道绑定的文件权限
     * @return 0-成功
     */
    char *fifo_path = "/tmp/myfifo";
    int res = mkfifo(fifo_path,0664);
    if(res !=0 ) {
        printf("mkfifo failed\n");
        // 打印错误编号
        // printf("errno[%d]\n",errno); 
        //当错误编号等于17时 表示的是文件已存在 此时不用退出 可以继续使用这个已存在的有名管道
        if( errno != 17) {
            exit(EXIT_FAILURE);
        }
    }

    // 对有名管道的特殊文件 创建fd
    int newfd = open(fifo_path,O_WRONLY);
    if(newfd == -1) {
        perror("create newfd failed");
        exit(1);
    }

    char buf[100];
    ssize_t read_num;

    //读控制台的数据
    while((read_num = read(STDIN_FILENO,buf,100)) > 0) {
        // 将从控制台读到的数据写入fifo管道中
        write(newfd, buf, read_num);
    }

    if(read_num < 0){
        perror("read");
        close(newfd);
        exit(1);
    }

    printf("send data finished process ending\n");
    close(newfd);

    // 释放管道 清除对应文件
    if(-1 == unlink(fifo_path)) {
        perror("unlink");
    }

    return 0;
}