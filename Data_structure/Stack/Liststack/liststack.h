#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct node {
    data_t data;
    struct node * next;
}listnote, *liststack;

liststack stack_create();

int stack_push(liststack s, data_t value);

data_t stack_pop(liststack s);

data_t stack_top(liststack s);

int stack_clear(liststack s);

int stack_empty(liststack s);

int stack_free(liststack s);









#endif