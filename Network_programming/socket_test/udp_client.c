#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

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
    char *sendBuf = malloc(sizeof(char) * 1024);

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

    socklen_t serverAddrLen = sizeof(serverAddr);
    socklen_t clientAddrLen = sizeof(clientAddr);

    // 收发数据

    do
    {
        // write(STDOUT_FILENO, "请输入要发送到信息:", 100);
        printf("请输入要发送的数据: \n");
        // 从控制台读取数据
        int sendLen = read(STDIN_FILENO, sendBuf, 1023);
        tmpRes = sendto(sockFd, sendBuf, sendLen, 0 , (struct sockaddr*)&serverAddr,serverAddrLen);
        handle_error("sendto", tmpRes);
        
        // 清空缓冲区 用来接收数据
        memset(sendBuf, 0, 1024);

        tmpRes = recvfrom(sockFd, sendBuf, 1024, 0 , (struct sockaddr*)&serverAddr,&serverAddrLen);
        handle_error("recvfrom", tmpRes);

        if(strncmp(sendBuf , "EOF", 3) != 0) {
            printf("收到服务端%s %d 返回的数据 %s\n",inet_ntoa(serverAddr.sin_addr),ntohs(serverAddr.sin_port), sendBuf);

        }

    } while (strncmp(sendBuf,"EOF",3) != 0);

    free(sendBuf);
    close(sockFd);
    
    return 0;
}

    