#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

// 定义一个异常处理的宏定义
#define handle_error(cmd,result)    \
        if(result < 0)              \
        {                           \
            perror(cmd);            \
            exit(EXIT_FAILURE);     \
        }  
        
        

void * read_from_client(void *arg)
{
    // 使用recv接收客户端发送的数据 打印到控制台
    char * readBuf = NULL;
    int client_fd = *(int*)arg;
    readBuf = malloc(sizeof(char) *BUFFER_SIZE);
    ssize_t cnt = 0;
    if (!readBuf) {
        perror("malloc server readBuf");
        return NULL;
    }

    // 接收数据
    /**
     * #include <sys/socket.h>
     * ssize_t recv(int sockfd, void *buf, size_t len, int flags);
     * @brief   从已连接到套接字接收数据
     * @param   sockfd: 已连接的套接字文件描述符    buf: 接收数据的缓冲区指针   len: 缓冲区长度     flags: 控制接收行为的标志位 一般写0
     * @return 成功返回接收到的字节数  0 - 对端正常关闭连接（可以理解为读完了 没东西可读了）    -1 - 出错
     */
    while((cnt = recv(client_fd, readBuf, BUFFER_SIZE, 0))) {
        if(cnt < 0 ) {
            perror("recv");
        }

        // 把数据打印到控制台
        fputs(readBuf, stdout);
    }

    printf(" 客户端请求关闭\n");
    free(readBuf);

    return NULL;

}

void * write_to_client(void * arg)
{
    // 服务端发送数据  读取控制台输入的数据 发送到客户端
    char * writeBuf = NULL;
    int client_fd = *(int*)arg;
    writeBuf = malloc(sizeof(char) *BUFFER_SIZE);
    ssize_t cnt = 0;
    if (!writeBuf) {
        perror("malloc server writeBuf");
        return NULL;
    }

    // 不断从控制台读取数据
    while (fgets(writeBuf, BUFFER_SIZE, stdin) != NULL) {
        // 把数据发送到客户端
        /**
         * #include <sys/socket.h>
         * ssize_t send(int sockfd, const void *buf, size_t len, int flags);
         * @brief   向已连接的套接字发送数据
         * @param   sockfd: 已连接的套接字文件描述符    buf: 待发送数据的缓冲区指针     len: 要发送的数据长度   flags: 控制发送行为的标志位 一般写0
         * @return 成功 返回实际发送到字节数   -1 - 出错
         */
        cnt = send(client_fd, writeBuf, BUFFER_SIZE, 0);
        if (cnt < 0) {
            perror("send");
        }
        
    }

    printf(" 接收到控制台的关闭请求 不再写入 关闭连接\n");
    /**
     * #include <sys/socket.h>
     * int shutdown(int sockfd, int how);
     * @brief 优雅关闭套接字连接
     * @param   sockfd: 要关闭的套接字文件描述符    how：关闭方式
     *                                              SHUT_RD: 关闭读通道 - 不再接收数据
     *                                              SHUT_WR: 关闭写通道 - 不再发送数据
     *                                              SHUT_RDWR: 同时关闭读写通道
     * @return 0 - 成功     -1 - 失败
     */
    shutdown(client_fd, SHUT_WR);
    free(writeBuf);

    return NULL;

}


int main(int argc, char const *argv[])
{
    int sockFd, tmpRes, clientFd;
    struct sockaddr_in serverAddr, clientAddr;
    pthread_t pidRead, pidWrite;

    // 清空
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // 填写服务端地址及端口号
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 监听所有网卡
    serverAddr.sin_port = htons(6666);

    // step1 创建socket套接字文件描述符
    /**
     * #include <sys/socket.h>
     * int socket(int domain, int type, int protocol);
     * @brief   创建套接字
     * @param   domain: 协议族/地址族       
     *              AF_INET: IPV4网络协议   一般用这个
     *              AF_INET6: IPV6网络协议
     *              AF_UNIX: 本地套接字（进程间通信）
     *              AF_PACKET: 底层数据包接口（如抓包）
     *          type: 套接字类型
     *              SOCK_STREAM: 用于TCP
     *              SOCK_DGRAM:  用于UDP
     *              SOCK_RAW:   原始套接字
     *          protocol: 写0 就行  自动选择默认协议
     * @return 成功返回新的套接字文件描述符   -1 - 失败
     */
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockFd);

    // step2 绑定地址和端口号
    /**
     * #include <sys/socket.h>
     * int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);
     * @brief 将套接字与特定的IP地址和端口号绑定
     * @param sockfd: 要绑定的套接字文件描述符  addr: 指向包含地址信息的结构体指针  addrlen: 地址结构体的长度
     * @return 0 - 成功     -1 - 失败
     */
    tmpRes = bind(sockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    handle_error("bind", tmpRes);

    // step3 进入监听状态
    /**
     * #include <sys/socket.h>
     * int listen(int sockfd, int backlog);
     * @brief 将套接字设置为被动监听模式
     * @param sockfd: 已绑定的套接字文件描述符  backlog: 等待连接队列的最大长度
     * @return 0 - 成功     -1 - 失败
     */
    tmpRes = listen(sockFd, 128);
    handle_error("listen", tmpRes);

    // step4 获取客户端的连接
    socklen_t clientAddrLen = sizeof(clientAddr);
    /**
     * #include <sys/socket.h>
     * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     * @brief 接受客户端连接请求
     * @param  sockfd: 处于监听状态的套接字  addr: 用于存储客户端地址信息   addrlen: 地址结构体的长度
     * @return 成功返回新的套接字描述符    -1 - 失败
     */
    clientFd = accept(sockFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    handle_error("accept", tmpRes);

    printf("与客户端%s %d建立连接 文件描述符是%d\n",inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port),clientFd);

    // 创建线程发消息
    pthread_create(&pidWrite, NULL, write_to_client,(void*)&clientFd);

    // 创建线程收消息
    pthread_create(&pidRead, NULL, read_from_client,(void*)&clientFd);

    // 阻塞主线程
    pthread_join(pidRead, NULL);
    pthread_join(pidWrite, NULL);

    // 释放资源
    close(clientFd);
    close(sockFd);


    return 0;
}
