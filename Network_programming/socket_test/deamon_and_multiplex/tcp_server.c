#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>

#define DATASIZE    1024

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        exit(EXIT_FAILURE);         \
    }

int sockFd;


void * rd_and_wr_thread(void * arg)
{
    // 读取客户端发送的数据
    int client_fd = *(int*)arg;
    char * rdBuf = NULL;
    char * wrBuf = NULL;
    ssize_t cnt = 0, sendCnt = 0;

    rdBuf = malloc(sizeof(char)*1024);
    if((!rdBuf)) {
        close(client_fd);
        perror("rdBuf malloc");
        exit(1);
    }

    wrBuf = malloc(sizeof(char)*1024);
    if((!wrBuf)) {
        free(rdBuf);
        rdBuf = NULL;
        close(client_fd);
        perror("rdBuf malloc");
        exit(1);
    }

    while((cnt = recv(client_fd, rdBuf, 1024, 0))) {
        if (cnt < 0) {
            perror("recv");
            continue;
        }

        // 接收数据打印到控制台
        printf("从%d客户端收到数据%s\n",client_fd, rdBuf);
        // 把收到的消息写到缓存
        strcpy(wrBuf, "收到\n");
        sendCnt = send(client_fd, wrBuf, 1024, 0);
        if(sendCnt < 0) {
            perror(" sendCnt");
        }    

    }

    // 当客户端输入ctrl + d时会退出循环
    // shutdown(client_fd, SHUT_RD);
    close(client_fd);
    free(rdBuf);
    free(wrBuf);

    return NULL;

}

void zombie_dealer(int sig)
{
    pid_t pid;
    int status;
    char buf[DATASIZE];
    memset(buf, 0, DATASIZE);

    while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            sprintf(buf, "子进程 : %d 以 %d 状态正常退出， 已被回收\n", pid, WEXITSTATUS(status));
            syslog(LOG_INFO, "%s", buf);
        } else if (WIFSIGNALED(status)) {
            sprintf(buf, "子进程 : %d 被 %d信号杀死 , 已被回收\n", pid, WTERMSIG(status));
            syslog(LOG_INFO, "%s", buf);

        } else {
            sprintf(buf, "子进程: %d 因其他原因退出, 已被回收\n",pid);
            syslog(LOG_INFO, "%s", buf);

        }
        
        
    }
}


void sigterm_handler(int sig)
{
    syslog(LOG_NOTICE, "服务端接收到守护进程发出的SIGTERM, 准备退出....");
    syslog(LOG_NOTICE, "释放sockfd");
    close(sockFd);
    syslog(LOG_NOTICE, "释放syslog连接, 服务端进程终止");
    closelog();

    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    int tmpRes;
    struct sockaddr_in serverAddr, clientAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    // 0.0.0.0
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(6666);

    // 创建socket套接字
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockFd);

    // 绑定地址
    socklen_t serverAddrLen = sizeof(serverAddr);
    tmpRes = bind(sockFd, (struct sockaddr *)&serverAddr, serverAddrLen);
    handle_error("bind", tmpRes);

    // 开始监听状态
    tmpRes = listen(sockFd, 128);

    socklen_t clientAddrLen = sizeof(clientAddr);

    // 注册信号处理函数 处理SIGCHLD信号 避免出现僵尸进程
    signal(SIGCHLD, zombie_dealer);
    // 处理SIGTERM函数 以优雅退出
    signal(SIGTERM, sigterm_handler);

    char logBuf[DATASIZE];
    memset(logBuf, 0, DATASIZE);

    // 接收client连接
    socklen_t cilentLen = sizeof(clientAddr);

    while (1) {
        int clientFd = accept(sockFd, (struct sockaddr*)&clientAddr, &cilentLen);
        handle_error("accpet",clientFd);

        // 创建子进程 和连接的客户端交互
        pid_t pidNew = fork();
        if (pidNew > 0 ) {
            sprintf(logBuf, " this is father , pid is %d, continue accepting...\n",getpid());
            syslog(LOG_INFO, " %s", logBuf);
            memset(logBuf, 0 , DATASIZE);
            close(clientFd);

            /* code */
        } else if (pidNew == 0) {
            // 关闭不会使用的sockfd
            close(sockFd);
            sprintf(logBuf, "与客户端%s %d 建立连接%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);
            syslog(LOG_INFO, "%s", logBuf);
            memset(logBuf, 0 ,DATASIZE);

            sprintf(logBuf, "新的服务端pid为 %d\n",getpid());
            syslog(LOG_INFO, "%s", logBuf);
            memset(logBuf, 0 ,DATASIZE);

            // 从客户端读取数据 并回复
            rd_and_wr_thread((void* )&clientFd);

            close(clientFd);
            exit(EXIT_SUCCESS);
        } else {

        }
    }
        
    return 0;
}
