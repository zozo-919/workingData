/**
 * @file    main.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */


#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "Dmathlib.h"

// ����ָ�����Ͷ���
typedef int (*math_func_int)(int, int);
typedef double (*math_func_double)(double, double);

void demonstrate_static_linking(void) {
    printf("=== ��̬������ʾ ===\n");
    
    // ��������
    printf("5 + 3 = %d\n", add(5, 3));
    printf("5 - 3 = %d\n", subtract(5, 3));
    printf("5 * 3 = %d\n", multiply(5, 3));
    printf("10.0 / 3.0 = %.2f\n", divide(10.0, 3.0));
    
    // �߼�����
    printf("5! = %d\n", factorial(5));
    printf("2^8 = %d\n", power(2, 8));
    printf("sqrt(25) = %.2f\n", square_root(25.0));
    printf("log(100) = %.2f\n", logarithm(100.0));
    printf("sin(��/2) = %.2f\n", sine(3.14159/2));
    printf("cos(��) = %.2f\n", cosine(3.14159));
    
    printf("\n");
}

void demonstrate_dynamic_loading(void) {
    printf("=== ��̬������ʾ ===\n");
    
    void *handle = dlopen("./lib/libmath.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "����: %s\n", dlerror());
        return;
    }
    
    // ��ȡ����ָ��
    math_func_int add_func = (math_func_int)dlsym(handle, "add");
    math_func_int multiply_func = (math_func_int)dlsym(handle, "multiply");
    math_func_double divide_func = (math_func_double)dlsym(handle, "divide");
    
    if (add_func && multiply_func && divide_func) {
        printf("��̬����: 5 + 3 = %d\n", add_func(5, 3));
        printf("��̬����: 5 * 3 = %d\n", multiply_func(5, 3));
        printf("��̬����: 10.0 / 3.0 = %.2f\n", divide_func(10.0, 3.0));
    } else {
        fprintf(stderr, "�޷��ҵ�����: %s\n", dlerror());
    }
    
    dlclose(handle);
    printf("\n");
}

int main() 
{
    printf("��ѧ�������ʾ����\n");
    printf("==================\n\n");
    
    // ��ʾ��̬����
    demonstrate_static_linking();
    
    // ��ʾ��̬����
    demonstrate_dynamic_loading();
    
    // ���Ծ�������
    printf("=== ����������ʾ ===\n");
    set_precision(4);
    printf("��ǰ����: %d λС��\n", get_precision());
    printf("10.0 / 3.0 = %.4f\n", divide(10.0, 3.0));
    
    // ���Դ�����
    printf("\n=== ��������ʾ ===\n");
    printf("������: %.2f\n", divide(10.0, 0.0));
    printf("�����׳�: %d\n", factorial(-5));
    printf("����ƽ����: %.2f\n", square_root(-25.0));
    
    return 0;
}