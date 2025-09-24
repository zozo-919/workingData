#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 打开文件
    FILE *  ioFile = fopen("io.txt","r");
    if (ioFile == NULL) {
        printf("open ioFile failed\n");
    }

    /**
     * int fgetc(FILE * __stream);
     * @brief 读取文件内容
     * @param FILE * __stream: 打开的文件
     * @return 成功读取到的一个字节 如果出错或到文件末尾 返回EOF 
    */
    char c = fgetc(ioFile);
#if 0
    // 只读一个字符
    if(c == EOF) {
        printf(" Fgetc failed\n");
    } else {
        printf("fgetc = [%c] \n",c);
    }
#else
    // 读整个文件
    while(c != EOF) {
        printf("%c",c);
        c = fgetc(ioFile);
    }
    printf("\n");

#endif
    

    //关闭文件
    int closeRes = fclose(ioFile);
    if(closeRes == EOF) {
        printf("Close ioFile failed\n");
    }
    


    return 0;
}
