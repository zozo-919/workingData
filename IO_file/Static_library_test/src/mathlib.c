/**
 * @file    mathlib.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

#include "mathlib.h"

int add(int a, int b) 
{
    return a + b;
}

int subtract(int a, int b) 
{
    return a - b;
}

int multiply(int a, int b) 
{
    return a * b;
}

double divide(double a, double b) 
{
    if (b == 0.0) return 0.0;
    return a / b;
}