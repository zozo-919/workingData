#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* *******************字节对齐验证******************* */

int main(void)
{
    // 原本结构体   占用32字节
    // typedef struct 
    // {
    //     char f;  1字节 + 填充1字节
    //     short g; 2字节
    //     int a;   4字节
    //     char b;  1字节
    //     char d;  1字节
    //     short h; 2字节 
    //     int i;   4字节
    //     char e;  1字节 + 填充7字节
    //     double c; 8字节
    // }my_struct_test;

    // 优化后结构体。占用24字节
    typedef struct 
    {
        double c;
        int a;
        int i;
        short g;
        short h;
        char f;      
        char b;
        char d;
        char e;
        
    }my_struct_test;

    my_struct_test str1;

    printf("%lu\n",sizeof(str1));
    
}