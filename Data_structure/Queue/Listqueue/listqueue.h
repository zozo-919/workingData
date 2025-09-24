#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef int data_t;

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

int queue_empty(linkqueue_t *lq);

int queue_clear(linkqueue_t * lq);

linkqueue_t * queue_free(linkqueue_t * lq);




#endif  /* LISTQUEUE_H */