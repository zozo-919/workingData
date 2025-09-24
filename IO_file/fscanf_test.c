#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 打开文件
    FILE *  ioFile = fopen("user.txt","r");
    if (ioFile == NULL) {
        printf("open ioFile failed\n");
    }

    /**
     * int fscanf(FILE * __restrict_stream, const char * __restrict_format, ...)
     * @brief 格式化读取文件内容
     * @param   __restrict_stream: 打开的文件  
     *          __restrict_format: 带有格式化字符串 （固定格式接收）
     *          ... 可变参数: 填写格式化的字符串 （接收数据提前声明的变量）
     * @return 成功匹配到的参数个数 失败返回0 报错或文件末尾返回EOF 
    */
    
    char name[50];
    int age;
    char wife[50];
    int scanfStr;

#if 0
    scanfStr = fscanf(ioFile,"%s %d %s",name,&age,wife);
    if(scanfStr == 0 || scanfStr == EOF) {
        printf("fscanf failed\n");
    } else {
        printf("%s在%d岁的时候爱上了%s\n",name,age,wife);
        printf("成功匹配到的参数有%d个\n",scanfStr);
    }
#else
    while ((scanfStr = fscanf(ioFile,"%s %d %s",name,&age,wife)) != EOF)
    {
        printf("%s在%d岁的时候爱上了%s\n",name,age,wife);
        printf("成功匹配到的参数有%d个\n",scanfStr);
    }
    
#endif   

    //关闭文件
    int closeRes = fclose(ioFile);
    if(closeRes == EOF) {
        printf("Close ioFile failed\n");
    }
    


    return 0;
}
