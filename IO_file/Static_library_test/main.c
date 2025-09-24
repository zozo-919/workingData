/**
 * @file    main.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

#include <stdio.h>
#include "mathlib.h"

int main() 
{
    printf("5 + 3 = %d\n", add(5, 3));
    printf("5 - 3 = %d\n", subtract(5, 3));
    printf("5 * 3 = %d\n", multiply(5, 3));
    printf("10.0 / 3.0 = %.2f\n", divide(10.0, 3.0));
    return 0;
}