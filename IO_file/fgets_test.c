#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 打开文件
    FILE *  ioFile = fopen("io.txt","r");
    if (ioFile == NULL) {
        printf("open ioFile failed\n");
    }

    /**
     * char * fgets(char * __restrict_s, int __size, FILE * __restrict_stream);
     * @brief 读取字符串
     * @param __restrict_s: 接收读出的字符串
     *          __size: 接收数据的长度
     *          __restrict_stream: 打开要读取的文件
     * @return 成功返回读到的字符串 失败返回EOF 
    */

    char strBuf[100];
    while(fgets(strBuf,sizeof(strBuf),ioFile)) {
        printf("%s",strBuf);
    }

    printf("\n");

    //关闭文件
    int closeRes = fclose(ioFile);
    if(closeRes == EOF) {
        printf("Close ioFile failed\n");
    }
    


    return 0;
}
