#ifndef SEQUEUE_H
#define SEQUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef int data_t;

#define N 128

typedef struct 
{
    /* data */
    data_t data[N];
    int front, rear;
}sequeue;

sequeue * queue_create(void);

int enqueue(sequeue * sq, data_t val);

data_t dequeue(sequeue * sq);

int queue_empty(sequeue *sq);

int queue_full(sequeue * sq);

int queue_clear(sequeue * sq);

sequeue * queue_free(sequeue * sq);



#endif /* SEQUEUE_H */