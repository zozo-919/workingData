#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>


int main(int argc, char const *argv[])
{
    printf("192.168.6.101 的16进制表示为 0x%X 0x%X 0x%X 0x%X \n",192, 168, 6, 101);

    //声明结构体接收数据
    /**
     * sockaddr_in 用于存储IP地址和端口号
     * struct sockaddr_in{
     *      sa_family_t sin_family   // 地址族（AF_INET 表示IPV4)
     *      in_port_t   sin_port     // 16位端口号 （网络字节序）
     *      struct in_addr sin_addr  // 32位IPV4地址（网络字节序）
     *      char  sin_zero[8]        // 填充字段 未使用 通常为0 
     * }
     */
    struct sockaddr_in server_addr;

    /**
     *  struct in_addr{
     *      in_addr_t s_addr    // 32位IPV4地址 （网络字节序）
     * }
     * 
     * in_addr_t 通常是uint32_t
     */
    struct in_addr server_in_addr;

    in_addr_t server_in_addr_t = 0;;

    memset(&server_addr, 0,sizeof(server_addr));
    memset(&server_in_addr, 0 ,sizeof(server_in_addr));

    // 不推荐使用  错误返回-1  -> 是一个正确的255.255.255.255值 容易引起误导
    /**
     * in_addr_t inet_addr(const char *cp);
     * @brief 将来自IPV4点分十进制表示法的Internet主机地址cp 转换为二进制形式的网络字节序
     * @param cp :主机地址
     * @return 如果输入无效通常返回-1 但-1是个有效地址（255.255.255.255）故不提倡用该方法
     */
    server_in_addr_t = inet_addr("192.168.6.101");
    printf("inet_addr: 0x%X\n", server_in_addr_t);


    // 推荐使用
    /**
     * int inet_aton(const char *cp, struct in_addr *inp);
     * @brief 将来自IPV4点分十进制表示法的Internet 主机地址cp转换为二进制形式并将其存储在inp指向的结构体中
     * @param cp: 主机地址  inp:存储二进制地址的结构体
     * @return 1 - 成功  0 - 失败
     */
    inet_aton("192.168.6.101", &server_in_addr);
    printf("inet_addr:[0x%X]\n", server_in_addr.s_addr);

    // 万能方法
    /**
     * int inet_pton(int af, const char *src, void *dst);
     * @brief 字符串格式转换为sockaddr_in格式
     * @param af: 通常为AF_INET用于IPV4地址 或AF_INET6用于IPV6
     *        src: 包含IP地址字符串的字符数组 如：192.168.6.101
     *        dst：指向一个struct in_addr结构体 用于存储转换后的二进制IP地址
     * @return 0 - 成功     1 - 地址输入错误    -1 - 发生错误
     */
    inet_pton(AF_INET, "192.168.6.101", &server_in_addr.s_addr);
    printf("inet_pton: 0x%X\n",server_in_addr.s_addr);

    // 结构体转换为字符串
    /**
     * char *inet_ntoa(struct in_addr in);
     * @brief 将IPV4地址从网络字节序的二进制形式转换为点分十进制的字符串表示形式
     * @param in: 一个struct in_addr结构体 包含要转换的IPV4地址（网络字节序）
     * @return  成功返回指向点分十进制字符串的指针 失败返回NULL
     */
    char * addr = inet_ntoa(server_in_addr);
    printf("addr = %s\n",addr);

    // 本地网络地址
    /**
     * in_addr_t inet_lnaof(struct in_addr in);
     * @brief 从IPV4地址中提取本地网络地址部分
     * @param in: 一个struct in_addr结构体 包含要处理的IPV4地址
     * @return 返回IPV4地址的主机部分
     */
    printf("本地网络地址: 0x%X\n",inet_lnaof(server_in_addr));

    // 网络号地址
    /**
     * in_addr_t inet_netof(struct in_addr in);
     * @brief 从IPV4地址中提取网络部分（网络号）
     * @param in: struct in_addr结构体 包含要处理的IPV4地址
     * @return 返回IPV4地址网络部分
     */
    printf("本地网络号地址: 0x%X\n",inet_netof(server_in_addr));



    return 0;
}
