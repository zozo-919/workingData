/**
 * @file    math_basic.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

 #include "Dmathlib.h"
#include <stdio.h>

static int precision = 2; // 默认精度

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0) {
        fprintf(stderr, "错误: 除以零!\n");
        return 0.0;
    }
    return a / b;
}

void set_precision(int digits) {
    if (digits >= 0 && digits <= 10) {
        precision = digits;
    }
}

int get_precision(void) {
    return precision;
}