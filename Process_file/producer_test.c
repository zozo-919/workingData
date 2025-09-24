#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mqueue.h>


int main(int argc, char const *argv[])
{
    // 创建消息队列
    struct mq_attr attr;
    // 有用的参数 表示消息队列的容量
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    // 被忽略的参数 在创建消息队列的时候用不到
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    char *mq_name = "/p_c_mq";

    mqd_t mqdes = mq_open(mq_name,O_RDWR|O_CREAT,0664, &attr);
    if((mqd_t)-1 == mqdes) {
        perror("mq_open fail");
        exit(1);
    }

    char write_buf[100];
    struct timespec timeinfo;
    // 不断接收控制台中的数据 发送到消息队列
    while (1)
    {
        memset(write_buf,0,100);
        clock_gettime(0,&timeinfo);
        timeinfo.tv_sec += 5;
        // 不断读取控制台输入的数据
        ssize_t read_count = read(STDIN_FILENO,write_buf,100);
        if(-1 == read_count) {
            perror("read");
            continue;
        } else if(read_count == 0) {
            //ctrl + d 关闭控制台
            printf("EOF, EXIT.....\n");
            char eof = EOF;
            if(-1 == mq_timedsend(mqdes,&eof,1,0,&timeinfo)) {
                perror("mq_timedsend");
            }
            break;
        }

        // 正常接收到控制台的可读信息
        if(-1 == mq_timedsend(mqdes,&write_buf,strlen(write_buf),0,&timeinfo)) {
            perror("mq_timedsend");
        }
        printf("从命令行接收到数据 已经发送给消息队列\n");
    }
    
    // 关闭消息队列描述符
    close(mqdes);

    return 0;
}
