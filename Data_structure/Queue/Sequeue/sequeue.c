#include "sequeue.h"


sequeue * queue_create(void)
{
    sequeue * sq = (sequeue*)malloc(sizeof(sequeue));
    if(sq == NULL) {
        printf("Malloc sq is failed\n");
        return NULL;
    }

    memset(sq->data, 0, N*sizeof(data_t));
    sq->front = 0;
    sq->rear = 0;

    return sq;
}

int enqueue(sequeue * sq, data_t val)
{
    if(sq == NULL)
        return -1;

    if((sq->rear + 1)% N == sq->front) {
        printf("sequeue is full\n");
        return -1;
    }

    sq->data[sq->rear] = val;
    sq->rear = (sq->rear + 1)% N;

    return 0;

}

data_t dequeue(sequeue * sq)
{
    data_t de_data;
    de_data = sq->data[sq->front];

    sq->front = (sq->front + 1) % N;

    return de_data;
}

int queue_empty(sequeue *sq)
{
    return (sq->front == sq->rear ? 1 : 0);
}

int queue_full(sequeue * sq)
{
    return (((sq->rear + 1) % N) == sq->front ? 1 : 0);
}

int queue_clear(sequeue * sq)
{
    sq->front = 0;
    sq->rear = 0;
    return 0 ;
}

sequeue * queue_free(sequeue * sq)
{
    free(sq);
    sq = NULL;

    return NULL;
}