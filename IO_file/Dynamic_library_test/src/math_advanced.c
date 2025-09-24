/**
 * @file    math_advanced.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

 #include "Dmathlib.h"
#include <math.h>
#include <stdio.h>

int factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "����: �׳˲���Ϊ����!\n");
        return 0;
    }
    if (n <= 1) return 1;
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int power(int base, int exponent) {
    if (exponent < 0) {
        fprintf(stderr, "����: ָ������Ϊ����!\n");
        return 0;
    }
    
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double square_root(double x) {
    if (x < 0) {
        fprintf(stderr, "����: ���ܶԸ�����ƽ��!\n");
        return 0.0;
    }
    return sqrt(x);
}

double logarithm(double x) {
    if (x <= 0) {
        fprintf(stderr, "����: ������������Ϊ����!\n");
        return 0.0;
    }
    return log(x);
}

double sine(double x) {
    return sin(x);
}

double cosine(double x) {
    return cos(x);
}