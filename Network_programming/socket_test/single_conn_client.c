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
#define handle_error(cmd,result)    \
        if(result < 0)              \
        {                           \
            perror(cmd);            \
            exit(EXIT_FAILURE) ;    \
        }  
        
        

void * read_from_server(void *arg)
{
    // 使用recv接收客户端发送的数据 打印到控制台
    char * readBuf = NULL;
    int client_fd = *(int*)arg;
    readBuf = malloc(sizeof(char) *1024);
    ssize_t cnt = 0;
    if (!readBuf) {
        perror("malloc server readBuf");
        return NULL;
    }

    // 接收数据
    while((cnt = recv(client_fd, readBuf, 1024, 0))) {
        if(cnt < 0 ) {
            perror("recv");
        }
        fputs(readBuf, stdout);
    }

    printf(" 服务端请求关闭\n");
    free(readBuf);

    return NULL;

}

void * write_to_server(void * arg)
{
    // 接收控制台输入的信息 写出去
    char * writeBuf = NULL;
    int client_fd = *(int*)arg;
    writeBuf = malloc(sizeof(char) *1024);
    ssize_t cnt = 0;
    if (!writeBuf) {
        perror("malloc server writeBuf");
        return NULL;
    }

    while (fgets(writeBuf,1024,stdin) != NULL) {
        cnt = send(client_fd, writeBuf, 1024, 0);
        if (cnt < 0) {
            perror("send");
        }
        
    }

    printf(" 接收到控制台的关闭请求 不再写入 关闭连接\n");
    shutdown(client_fd, SHUT_WR);
    free(writeBuf);

    return NULL;

}


int main(int argc, char const *argv[])
{
    int sockfd, tmpRes;
    struct sockaddr_in serverAddr, clientAddr;
    pthread_t pidRead, pidWrite;

    // 清空
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // // // 填写客户端地址
    clientAddr.sin_family = AF_INET;
    // clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, "192.168.1.47", &clientAddr.sin_addr);
    clientAddr.sin_port = htons(8888);

    // 填写服务端地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = htons(6666);

    // step1 客户端create_socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // // step2 绑定地址
    tmpRes = bind(sockfd, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    handle_error("bind", tmpRes);

    // step3 客户端连接服务器
    /**
     * #include <sys/socket.h>
     * int connet(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     * @brief  建立与远程服务器的连接
     * @param  sockfd: 已创建的套接字描述符    addr: 指向目标服务器地址结构体的指针    addrlen: 地址结构体的长度
     * @return 0 - 成功     -1 - 失败
     */
    tmpRes = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    handle_error("connect", tmpRes);

    printf("连接上服务端%s %d建立连接 \n",inet_ntoa(serverAddr.sin_addr),ntohs(serverAddr.sin_port));

    // 创建线程发消息
    pthread_create(&pidWrite, NULL, write_to_server,(void*)&sockfd);

    // 创建线程收消息
    pthread_create(&pidRead, NULL, read_from_server,(void*)&sockfd);

    // 阻塞主线程
    pthread_join(pidRead, NULL);
    pthread_join(pidWrite, NULL);

    // 释放资源
    close(sockfd);


    return 0;
}

