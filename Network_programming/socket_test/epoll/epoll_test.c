#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEVER_PORT 6666
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10

#define handle_error(cmd, result)       \
    if (result < 0)                     \
    {                                   \
        perror(cmd);                    \
        exit(EXIT_FAILURE);             \
    }

char *rdBuf = NULL;
char *wrBuf = NULL;

void init_buf(void)
{
    rdBuf = malloc(sizeof(char)*BUFFER_SIZE);
    if (!rdBuf) {
        perror("malloc server rdBuf");
        exit(EXIT_FAILURE);
    }

    wrBuf = malloc(sizeof(char)*BUFFER_SIZE);
    if (!wrBuf) {
        perror("malloc server wrBuf");
        exit(EXIT_FAILURE);
    }

    memset(rdBuf, 0 , BUFFER_SIZE);
    memset(wrBuf, 0 , BUFFER_SIZE);  
}

void clear_buf(char * buf)
{
    memset(buf, 0 , BUFFER_SIZE);
    
}

void set_nonblocking(int sockfd)
{
    int opts = fcntl(sockfd, F_GETFL);
    handle_error("fcntl(F_GETFL)", opts);

    opts |= O_NONBLOCK;
    int res = fcntl(sockfd, F_SETFL, opts);
    handle_error("fcntl(F_SETFL)", res);
}

int main(int argc, char const *argv[])
{
    // 初始化读写缓冲
    init_buf();
    
    // 声明sockFd、clientfd和函数返回状态变量
    int sockFd, clientFd, tmpRes;
    
    // 声明服务端和客户端
    struct sockaddr_in serverAddr, clientAddr;

    // 初始化 结构体
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // 声明IPV4协议
    serverAddr.sin_family = AF_INET;
    // 绑定0.0.0.0地址 主机字节序转换成网络字节序
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 声明端口 主机字节序转换成网络字节序
    serverAddr.sin_port = htons(SEVER_PORT);

    // 创建 server socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockFd);

    // 绑定地址
    socklen_t serverAddrLen = sizeof(serverAddr);
    tmpRes = bind(sockFd, (struct sockaddr*)&serverAddr, serverAddrLen);

    // 进入监听模式
    tmpRes = listen(sockFd, 128);
    handle_error("listen", tmpRes);

    // 将sockFd设置为非阻塞模式
    set_nonblocking(sockFd);

    int epollFd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];

    // 创建epoll
    epollFd = epoll_create1(0);
    handle_error("epoll_create1", epollFd);

    // 将sockFd加入到感兴趣列表
    ev.data.fd = sockFd;
    ev.events = EPOLLIN;
    tmpRes = epoll_ctl(epollfd, EPOLL_CTL_ADD, sockFd, &ev);
    handle_error("epoll_ctl", tmpRes);

    socklen_t clientAddrLen = sizeof(clientAddr)
    
    // 接受client连接
    while (1)
    {
        // 第一个循环   ->  只等待客户端连接进来    ->  nfds表示有多少个客户端连接
        // 第n次循环    ->  既有新的客户端连接进来 也有 旧的客户端发消息过来
        nfds = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        handle_error("epoll_wait", nfds);

        for (int i = 0; i < nfds; i++)
        {
            // 第一次循环   只会走这个逻辑
            if (events[i].data.fd == sockFd)
            {
                // 因为里面有客户端连接了 直接获取连接
                clientFd = accept(sockFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
                handle_error("accept", clientFd);
                // 修改为非阻塞状态
                set_nonblocking(clientFd);

                printf("与客户端%s %d 建立连接%d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);
                ev.data.fd = clientFd;

                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clientFd, &ev);
                
                // 第n次连接 -> 
            } else if (events[i].events & EPOLLIN) {
                int cnt = 0, sendCnt = 0;
                clientFd = events[i].data.fd;
                while ((cnt = recv(clientFd, rdBuf, BUFFER_SIZE,0)) > 0)
                {
                    printf("recv message from clientFd: %d : %s\n",clientFd, rdBuf);
                    clear_buf(rdBuf);

                    strcpy(wrBuf,"recved...\n");
                    sendCnt = send(clientFd, wrBuf, strlen(wrBuf), 0);
                    handle_error("send",sendCnt);
                    clear_buf(wrBuf);
                }

                if (cnt == -1 && errno == EAGAIN)
                {
                    printf("来自客户端clientFd: %d当前批次的数据已经读取完毕 继续监听文件描述符集\n",clientFd);
                } else if (cnt == 0)
                {
                    printf("客户端clientFd: %d 请求关闭连接.....\n", clientFd);
                    strcpy(wrBuf,"recved shutdown signal\n");
                    sendCnt = send(clientFd, wrBuf, strlen(wrBuf), 0);
                    handle_error("send",sendCnt);
                    clear_buf(wrBuf);

                    // 从epoll文件描述符集中移除clientFd
                    printf("从epoll文件描述符集中移除clientFd: %d \n",clientFd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, clientFd, NULL);

                    printf("释放clientFd: %d 资源\n",clientFd);
                    shutdown(clientFd, SHUT_WR);
                    close(clientFd);
                    
                }                               
            }   
        }
    }

    // 释放资源
    close(epollfd);
    close(sockFd);
    free(rdBuf);
    free(wrBuf);   

    return 0;
}

    