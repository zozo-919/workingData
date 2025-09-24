#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mqueue.h>

/*******************本文在macOS中无法编译成功 macos系统不支持POSIX消息队列 ******************* */

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
    char *mq_name = "/father_son_mq";

    /**
     * typedef int mqd_t;
     * mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
     * @brief 创建或打开一个已存在的POSIX消息队列 消息队列是通过名称唯一标识的
     * @param name: 消息队列的名称 命名规则 必须以/开头 中间包含若干字符但不能有/     
     *        oflag:指定消息队列的控制权限
     *          （1）O_RDONLY 打开的消息队列 只用于接收消息
     *          （2）O_WRONLY 打开的消息队列 只用于发送消息
     *          （3）O_RDWR 打开的消息队列 用于收发消息
     *           以上3个选项可与下列相或操作
     *              O_CLOEXEC 设置close-on-exec 标记 该标记表示执行exec时关闭文件描述符
     *              O_CREAT 当文件不存在时创建 如果指定了这一标记 需要额外提供mode和attr参数
     *              O_EXCL 创建一个当前进程独占的消息队列 要同时指定O_CREAT 要求创建的消息队列不存在 否则会失败
     *              O_NONBLOCK 以非阻塞模式打开消息队列 如果设置了该选项 在默认情况下收发消息发送阻塞时 会转而失败
     *        mode: 每个消息队列在mqueue文件系统对应一个文件 mode时用来指定消息队列对应文件的权限的
     *        attr: 属性信息 如果为NULL 则队列以默认属性创建
     *              {
     *                  mq_flags: 标记 对于mq_open 忽略它
     *                  mq_maxmgs: 队列可以容纳的消息的最大数量
     *                  mq_msgsize: 单条消息的最大允许大小 以字节为单位
     *                  mq_curmsgs: 当前队列中的消息数量 对于mq_open 忽略它
     *              }
     * @return mqd_t 成功则返回消息队列描述符 失败返回（mqd_t)-1 
     */
    mqd_t mqdes = mq_open(mq_name,O_RDWR|O_CREAT,0664, &attr);
    if((mqd_t)-1 == mqdes) {
        perror("mq_open fail");
        exit(1);
    }

    //创建父子进程
    pid_t newPid = fork();
    if(0 > newPid) {
        perror("fork");
        exit(1);
    } else if(0 == newPid) {
        // 子进程 等待接收消息队列中的信息
        char read_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            // 清空接收数据的缓冲区
            memset(send_buf,0,100);
            // 设置接收数据的等待时间
            /**
             * int clock_gettime(clockid_t clockid, struct timespec *tp);
             * @brief 获取以struct timespec形式表示的clockid指定的时钟
             * @param clockid 特定时钟的标识符 常用的是CLOCK_REALTIME 表示当前真实时间的时钟 tp：用于接收时间信息的缓存
             * @return 成功返回0 失败返回-1
             */
            clock_gettime(CLOCK_REALTIME,&time_info);
            time_info.tv_sec += 15;
            // 接收消息队列的数据 打印到控制台
            /**
             * int mq_timedreceive(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio, const struct timespec *abs_timeout)
             * @brief 从消息队列中取走最早入队且权限最高的消息 将其放入msg_ptr指向的缓存中 如果消息队列为空 默认情况下调用阻塞
             * @param mqdes 消息队列描述符  msg_ptr 接收消息的缓存 msg_len msg_ptr指向的缓存区大小 大于等于mq_msgsize属性指定的队列单条消息最大字节数
             *        abs_timeout 阻塞时等待的最晚时间节点 同mq_timedsend
             * @return ssize_t 成功则返回接收到的消息的字节数 失败返回-1
             */
            if(-1 == mq_timedreceive(mqdes,read_buf,100,NULL,&time_info)) {
                perror("mq_timereceive");
            }

            printf("子进程接收到数据 %s\n",read_buf);
        }

    } else {
        // 父进程 发送消息到消息队列中
        char send_buf[100];
        /**
         * struct timespec
         * @brief 时间结构体 提供纳秒级UNIX时间戳
         * {
         *   time_t tv_sec;  秒
         *   long   tv_nsec; 纳秒
         * }
         */
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            //清空处理buf
            memset(send_buf,0,100);
            sprintf(send_buf,"父进程第%d次发生消息\n",(int)(i+1));
            // 获取当前的具体时间
            clock_gettime(CLOCK_REALTIME,&time_info);
            // 等待5s
            time_info.tv_sec +=5;
            // 发送消息
            /**
             * int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio, const struct timespec *abs_timeout);
             * @brief 将msg_ptr指向的消息队列追加到消息队列描述符mqdes指向的消息队列的尾部
             * @param mqdes: 消息队列描述符    msg_ptr: 指向消息的指针    msg_len: msg_ptr指向的消息长度 不能超过队列的mq_msgsize属性指定的队列最大容量 长度为0的消息是被容许的
             *        msg_prio:  一个非负整数 指定了消息的优先级 消息队列中的数据按照优先级降序排列 如果新旧消息优先级相同 则新的消息排在后面
             *        abs_timeout: 指向struct timespec 类型的对象 指定了阻塞等待的最晚时间 如果消息队列已满 且abs_timeout指定的时间节点已过期 则调用立即返回
             * @return 成功返回 0  失败返回-1
             */
            if(-1 == mq_timedsend(mqdes, send_buf, strlen(send_buf),0, &time_info)) {
                perror("mq_timesend");
            }
            printf("父进程发送一条消息 休眠1s\n");
            sleep(1);
        }
        
        
    }

    // 父子进程都需释放消息队列的引用
    close(mqdes);
    // 清除消息队列只需要执行一次
    if(newPid > 0) {
        /**
         * int mq_unlink(const char *name);
         * @brief 清除name对应的消息队列 mqueue文件系统中的对应文件被立即清除 消息队列本身的清除必须等待所有指向该消息队列的描述符全部关闭后才会发生
         * @param name: 消息队列名称
         * @return 成功返回0 失败返回-1
         */
        mq_unlink(mq_name);
    }
    return 0;
}
