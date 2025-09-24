/**
 * @file    Dmathlib.h
 * @author  Zozo@971211
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

 #ifndef DMATHLIB_H
#define DMATHLIB_H

#ifdef __cplusplus
extern "C" {
#endif

// ��������
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
double divide(double a, double b);

// �߼�����
int factorial(int n);
int power(int base, int exponent);
double square_root(double x);
double logarithm(double x);
double sine(double x);
double cosine(double x);

// ���ߺ���
void set_precision(int digits);
int get_precision(void);

#ifdef __cplusplus
}
#endif

#endif // DMATHLIB_H