#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct 
{
    /* data */
    data_t * data;
    int maxLen;
    int top;
}sqstack;


sqstack * stack_create(int len);
int stack_push(sqstack * s, data_t value);
data_t stack_pop(sqstack * s);
data_t stack_top(sqstack *s);
int stack_free(sqstack *s);
int stack_empty(sqstack *s);
int stack_full(sqstack *s);


#endif /* SQSTACK_H */
