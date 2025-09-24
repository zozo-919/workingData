#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define DATASIZE    1024

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        exit(EXIT_FAILURE);         \
    }

void * read_from_server(void *argv)
{
    int sockFd = *(int*)argv;
    char * rdBuf = NULL;
    ssize_t cnt = 0;

    rdBuf = malloc(sizeof(char) * DATASIZE);
    if (!rdBuf) {
        perror("malloc rdBuf");
        exit(EXIT_FAILURE);
    }

    while ((cnt = recv(sockFd,rdBuf, DATASIZE, 0))) {
        if(cnt < 0) {
            perror("recv");
            continue;
        }
        fputs(rdBuf, stdout);
    }

    printf("收到服务端的终止信号......\n");
    free(rdBuf);

    return NULL;
}

void * write_to_server(void *argv)
{
    int sockFd = *(int*)argv;
    char * wrBuf = NULL;
    ssize_t sendCnt = 0;

    wrBuf = malloc(sizeof(char) * DATASIZE);
    if (!wrBuf) {
        perror("malloc wrBuf");
        shutdown(sockFd, SHUT_WR);
        exit(EXIT_FAILURE);
    }

    while (fgets(wrBuf, DATASIZE, stdin) != NULL) {
        sendCnt = send(sockFd, wrBuf, DATASIZE, 0);
        if(sendCnt < 0) {
            perror("send");
            continue;
        }
    }

    printf("接收到命令行的终止信号 不再写入  关闭连接 ....\n");
    shutdown(sockFd, SHUT_WR);
    free(wrBuf);

    return NULL;
    
}

int main(int argc, char const *argv[])
{
    int sockFd, tmpRes;
    pthread_t pidRD, pidWR;
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    serverAddr.sin_family = AF_INET;
    // 连接本机 127.0.0.1
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serverAddr.sin_port = htons(6666);

    // 创建socket套接字
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockFd);

    // 连接server 
    socklen_t serverAddrLen = sizeof(serverAddr);
    tmpRes = connect(sockFd, (struct sockaddr *)&serverAddr, serverAddrLen);
    handle_error("connect", tmpRes);

    // 创建一个子线程来 读取服务端数据 并打印到控制台
    pthread_create(&pidRD, NULL, read_from_server, (void*)&sockFd);
    // 创建一个子线程 从命令行读取数据 发送至服务端
    pthread_create(&pidWR, NULL, write_to_server, (void*)&sockFd);


    // 等待子线程退出 
    pthread_join(pidRD, NULL);
    pthread_join(pidWR, NULL);
    
    // 释放资源
    close(sockFd);
    
    return 0;
}

    