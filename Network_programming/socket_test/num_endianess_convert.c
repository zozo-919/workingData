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
    // 声明两个端口号
    unsigned short localNum = 0x1f,networkNum = 0;
    /**
     * uint16_t htons(uint16_t hostshort);
     * @brief 将无符号短整数 hostshort 从主机字节顺序(h)转换为网络字节顺序(n);
     */
    networkNum = htons(localNum);
    printf("将主机字节序无符号整数0x%hX转化为网络字节序0x%hX\n",localNum,networkNum);


    /**
     * uint16_t ntohs(uint16_t netshort);
     * @brief 将无符号短整数netshort 从网络字节顺序(n)转换为主机字节顺序(h);
     */
    localNum = ntohs(networkNum);
    printf("将主机字节序无符号整数0x%hX转化为网络字节序0x%hX\n",networkNum,localNum);

    return 0;
}
