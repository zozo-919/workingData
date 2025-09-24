#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>


// 定义一个异常处理的宏定义
#define handle_error(cmd,result) \
        if(result < 0)           \
        {                        \
            perror(cmd);         \
            return -1 ;          \
        }  


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

int main(int argc, char const *argv[])
{
    int sockFd, tmpRes;
    struct sockaddr_in serverAddr, clientAddr;

    // 清空
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // 填写服务端地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(6666);

    // step1 创建套接字
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockFd);

    // step2 绑定地址
    tmpRes = bind(sockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    handle_error("bind", tmpRes);

    // step3 进入监听状态
    tmpRes = listen(sockFd, 128);
    handle_error("listen", tmpRes);

    // step4 获取客户端的连接 需要能够接收多个连接
    socklen_t cilentLen = sizeof(clientAddr);
    while (1)
    {

        int clientFd = accept(sockFd, (struct sockaddr*)&clientAddr, &cilentLen);
        handle_error("accpet",clientFd);
        printf("与客户端%s %d 建立连接%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);

        pthread_t pidRDWR;

        // 与每一个客户端使用一个线程交互 把客户端发送的消息打印到控制台 回复收到
        if(pthread_create(&pidRDWR, NULL, rd_and_wr_thread, (void*)&clientFd)) {
            perror("create pthread");
        }

        // 需要等待线程结束 但是不能挂起等待
        pthread_detach(pidRDWR);

    }

    // 释放资源
    close(sockFd);


    return 0;
}
