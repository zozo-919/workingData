#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* *******************�ֽڶ�����֤******************* */

int main(void)
{
    // ԭ���ṹ��   ռ��32�ֽ�
    // typedef struct 
    // {
    //     char f;  1�ֽ� + ���1�ֽ�
    //     short g; 2�ֽ�
    //     int a;   4�ֽ�
    //     char b;  1�ֽ�
    //     char d;  1�ֽ�
    //     short h; 2�ֽ� 
    //     int i;   4�ֽ�
    //     char e;  1�ֽ� + ���7�ֽ�
    //     double c; 8�ֽ�
    // }my_struct_test;

    // �Ż���ṹ�塣ռ��24�ֽ�
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