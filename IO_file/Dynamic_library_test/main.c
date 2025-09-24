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

// 函数指针类型定义
typedef int (*math_func_int)(int, int);
typedef double (*math_func_double)(double, double);

void demonstrate_static_linking(void) {
    printf("=== 静态链接演示 ===\n");
    
    // 基础运算
    printf("5 + 3 = %d\n", add(5, 3));
    printf("5 - 3 = %d\n", subtract(5, 3));
    printf("5 * 3 = %d\n", multiply(5, 3));
    printf("10.0 / 3.0 = %.2f\n", divide(10.0, 3.0));
    
    // 高级运算
    printf("5! = %d\n", factorial(5));
    printf("2^8 = %d\n", power(2, 8));
    printf("sqrt(25) = %.2f\n", square_root(25.0));
    printf("log(100) = %.2f\n", logarithm(100.0));
    printf("sin(π/2) = %.2f\n", sine(3.14159/2));
    printf("cos(π) = %.2f\n", cosine(3.14159));
    
    printf("\n");
}

void demonstrate_dynamic_loading(void) {
    printf("=== 动态加载演示 ===\n");
    
    void *handle = dlopen("./lib/libmath.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "错误: %s\n", dlerror());
        return;
    }
    
    // 获取函数指针
    math_func_int add_func = (math_func_int)dlsym(handle, "add");
    math_func_int multiply_func = (math_func_int)dlsym(handle, "multiply");
    math_func_double divide_func = (math_func_double)dlsym(handle, "divide");
    
    if (add_func && multiply_func && divide_func) {
        printf("动态加载: 5 + 3 = %d\n", add_func(5, 3));
        printf("动态加载: 5 * 3 = %d\n", multiply_func(5, 3));
        printf("动态加载: 10.0 / 3.0 = %.2f\n", divide_func(10.0, 3.0));
    } else {
        fprintf(stderr, "无法找到函数: %s\n", dlerror());
    }
    
    dlclose(handle);
    printf("\n");
}

int main() 
{
    printf("数学运算库演示程序\n");
    printf("==================\n\n");
    
    // 演示静态链接
    demonstrate_static_linking();
    
    // 演示动态加载
    demonstrate_dynamic_loading();
    
    // 测试精度设置
    printf("=== 精度设置演示 ===\n");
    set_precision(4);
    printf("当前精度: %d 位小数\n", get_precision());
    printf("10.0 / 3.0 = %.4f\n", divide(10.0, 3.0));
    
    // 测试错误处理
    printf("\n=== 错误处理演示 ===\n");
    printf("除以零: %.2f\n", divide(10.0, 0.0));
    printf("负数阶乘: %d\n", factorial(-5));
    printf("负数平方根: %.2f\n", square_root(-25.0));
    
    return 0;
}