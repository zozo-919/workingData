#include "listqueue.h"

linkqueue_t * queue_create(void)
{
    linkqueue_t * lq = (linkqueue_t*)malloc(sizeof(linkqueue_t));
    if(lq == NULL)
        return NULL;

    lq->front = (linklist_t)malloc(sizeof(listnode_t));
    lq->rear = lq->front;
    if(lq->front == NULL)
        return NULL;

    lq->front->data = 0;
    lq->front->next = NULL;

    return lq;

}

int enqueue(linkqueue_t * lq, data_t val)
{
    if(lq == NULL)
        return -1;

    linklist_t p = (linklist_t)malloc(sizeof(listnode_t));
    if(p == NULL)
        return -1;

    // p->data = val;  等价于 下面 lq->rear->data = val ;
    lq->front->next = p;  // 等价于 lq->rear->next = p;
    lq->rear = p;
    lq->rear->data = val;

    return 0;

    
}

data_t dequeue(linkqueue_t * lq)
{
    linklist_t p;
    p = lq->front;
    lq->front = lq->front->next;

    free(p);
    p = NULL;

    return lq->front->data;


}

int queue_empty(linkqueue_t *lq)
{
    return (lq->front == lq->rear ? 1:0);
}


int queue_clear(linkqueue_t * lq)
{
    linklist_t p ;
    while(lq->front != lq->rear) {
        p = lq->front;
        lq->front = lq->front->next;
        free(p);
        p = NULL;
    }

    return 0;
}


linkqueue_t * queue_free(linkqueue_t * lq)
{
    linklist_t p;
    while(lq->front) {
        p = lq->front;
        lq->front = lq->front->next;
        free(p);
        p = NULL;
    }

    free(lq);
    lq = NULL;

    return NULL;
}