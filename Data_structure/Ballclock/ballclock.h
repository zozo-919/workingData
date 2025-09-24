#ifndef BALLCLOCK_H
#define BALLCLOCK_H

/* 球钟问题 */

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


// typedef int data_t;

typedef struct node_t{
    data_t data;
    struct node_t * next;
}listnode_t, *linklist_t;

typedef struct {
    linklist_t front, rear;
} linkqueue_t;

linkqueue_t * queue_create(void);
int enqueue(linkqueue_t * lq, data_t val);
data_t dequeue(linkqueue_t * lq);

sqstack * stack_create(int len);
int stack_full(sqstack *s);
int stack_push(sqstack * s, data_t value);
data_t stack_pop(sqstack * s);

int queue_empty(linkqueue_t *lq);



int check_queue(linkqueue_t * lq);



#endif /* BALLCLOCK_H */