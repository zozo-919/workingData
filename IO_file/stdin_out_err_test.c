#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    char *str = malloc(100);
    //从标准输入中读取数据
    fgets(str,100,stdin);
    
    printf("hello %s \n",str);

    //标准输出
    fputs(str,stdout);

    //错误输出
    fputs(str,stderr);


    return 0;
}
