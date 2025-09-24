#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define handle_error(cmd, result)   \
    if (result < 0)                 \
    {                               \
        perror(cmd);                \
        exit(EXIT_FAILURE);         \
    }

int main(int argc, char const *argv[])
{  
    // udp协议完成客户端和服务端的通讯
    // EOF 作为关闭的信号

    int sockFd, tmpRes;
    char *recvBuf = malloc(sizeof(char) * 1024);

    struct sockaddr_in serverAddr, clientAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6666);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // UDP通信流程
    // step1 创建socket接字  注意第二个参数 与tcp不同
    sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket",sockFd);

    // step2 服务端绑定地址及端口
    socklen_t serverAddrLen = sizeof(serverAddr);
    tmpRes = bind(sockFd, (struct sockaddr *)&serverAddr, serverAddrLen);
    handle_error("bind",tmpRes);

    socklen_t clientAddrLen = sizeof(clientAddr);

    // 收发数据

    do
    {
        memset(recvBuf, 0 ,1024);
        // 接收数据
        tmpRes = recvfrom(sockFd, recvBuf,1024,0,(struct sockaddr*)&clientAddr, &clientAddrLen);
        handle_error("recvfrom", tmpRes);
        if (strncmp(recvBuf,"EOF",3) !=0 ) {
            printf("接收到客户端 %s  %d 信息: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), recvBuf);
            strcpy(recvBuf, "OK\n");
        } else {
            printf("收到结束信息 准备关闭\n");
        }

        // 回复数据
        tmpRes = sendto(sockFd, recvBuf, 4, 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        handle_error("sendto", tmpRes);

    } while (strncmp(recvBuf,"EOF",3) != 0);

    free(recvBuf);
    close(sockFd);
    
    return 0;
}

    