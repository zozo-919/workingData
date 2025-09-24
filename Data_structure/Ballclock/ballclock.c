#include "ballclock.h"
// #include "../Stack/Sqstack/sqstack.h"
// #include "../Queue/Listqueue/listqueue.h"

/*          球钟问题 
 * 设初始球队列的球数为27 球钟的三个指示器初态均为空 要经过多久 球队列才能恢复到原来的顺序
 **/

int main(int argc, const char *argv[])
{
    int count = 0;
    /* 创建 链式队列 存放27个球 */
    linkqueue_t * ballListQueue = queue_create();
    if(ballListQueue == NULL) {
        printf("Create ballListQueue failed\n");
        return -1;
    }

    /* 把球按顺序存入队列 */
    for(int ballNum = 1; ballNum <= 27; ballNum++) {
        // if(!enqueue(ballListQueue, ballNum)) {
        //     printf(" val=[%d] enqueue failed\n",ballNum);
        //     return -1;
        // }

        enqueue(ballListQueue, ballNum);
    }

#if 0
    while (!queue_empty(ballListQueue)) {
        /* code */
        printf("%d ",dequeue(ballListQueue));
    }

    printf("\n");
#endif
    #if 1

    /*创建小时、5-min、min 三个顺序栈 来作为各自时钟计时器 存放队列中的球 */
    sqstack *s_hour = NULL, *s_five = NULL, *s_min = NULL;
    int hourMaxLen = 11, fiveMaxLen = 11, minMaxLen = 4;
    
    s_hour = stack_create(hourMaxLen);
    if(s_hour == NULL) {
        printf("create hour stack failed\n");
        return -1;
    }

    s_five = stack_create(fiveMaxLen);
    if(s_five == NULL) {
        printf("create s_five stack failed\n");
        return -1;
    }

    s_min = stack_create(minMaxLen);
    if(s_min == NULL) {
        printf("create s_min stack failed\n");
        return -1;
    }

    while(1) {
        count++;
        int dequeueVal = dequeue(ballListQueue);

        if(!stack_full(s_min)) {
            int ret = stack_push(s_min,dequeueVal);
            if(ret) {
                printf("s_min stack_push failed\n");
                return -1;
            }
        } else {

            /* 1分钟的计时器栈 弹出 并入队 */
            for(int i = 0; i< minMaxLen; i++) {
                enqueue(ballListQueue,stack_pop(s_min));
            }

            if(!stack_full(s_five)) {
                int min_ret = stack_push(s_five,dequeueVal);
                if(min_ret) {
                    printf("s_five stack_push failed\n");
                    return -1;
                }
            } else {

                /* 5分钟的计时器栈 弹出 并入队 */
                for(int i = 0; i< fiveMaxLen; i++) {
                    enqueue(ballListQueue,stack_pop(s_five));
                }

                if(!stack_full(s_hour)) {
                    int hour_min = stack_push(s_hour,dequeueVal);
                    if(hour_min) {
                        printf("s_hour stack_push failed\n");
                        return -1;
                    }
                } else {

                    /* 小时计时器栈 弹出 并入队 */
                    for(int i = 0; i< hourMaxLen; i++) {
                        enqueue(ballListQueue,stack_pop(s_hour));
                    }

                    enqueue(ballListQueue,dequeueVal);

                    if(check_queue(ballListQueue)) {
                        break;
                    }

                }
            }
        }

    }

    printf("total: %d\n",count);

    while (!queue_empty(ballListQueue)) {
        /* code */
        printf("%d  ",dequeue(ballListQueue));
    }

    printf("\n");
#endif


    return 0;
}



linkqueue_t * queue_create(void)
{
    linkqueue_t * lq = (linkqueue_t*)malloc(sizeof(linkqueue_t));
    if(lq == NULL) {
        printf("malloc linkqueue_t failed\n");
        return NULL;
    }

    // lq->front = lq->rear = (linklist_t)malloc(sizeof(listnode_t));
    lq->front = (linklist_t)malloc(sizeof(listnode_t));
    if(lq->front == NULL) {
        printf("lq->front malloc failed\n");
        return NULL;
    }

    lq->rear = lq->front;

    lq->front->data = lq->rear->data = 0;
    lq->front->next = lq->rear->next = NULL;

    return lq;

}

int enqueue(linkqueue_t * lq, data_t val)
{
    if(lq == NULL) {
        printf("lq is null\n");
        return -1;
    }

    linklist_t p = (linklist_t)malloc(sizeof(listnode_t));
    if(p == NULL) {
        printf("p is null\n");
        return -1;
    }

    // p->data = val;  //等价于 下面 lq->rear->data = val ;
    lq->rear->next = p; //// 这里必须是 lq->rear->next = p;
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

int check_queue(linkqueue_t * lq)
{
    linklist_t p;
    
    p = lq->front->next;
    while(p && p->next) {
        if(p->data < p->next->data){
            p = p->next;
        } else {
            return 0;
        }

    }

    return 1;

}

sqstack * stack_create(int len) 
{
    sqstack * s = (sqstack*)malloc(sizeof(sqstack));
    if(s == NULL) {
        printf("sqstack s malloc failed\n");
        return NULL;
    }

    s->data = (data_t*)malloc(sizeof(data_t)*len);
    if(s->data == NULL) {
        printf("s.data malloc failed\n");
        free(s);
        s = NULL;
        return NULL;
    }

    memset(s->data, 0, len*sizeof(data_t));
    s->maxLen = len;
    s->top = -1;

    return s;
}



int stack_full(sqstack *s)
{
    if(s == NULL) {
        printf("the stack is not exist\n");
        return -1;
    }

    return (s->top == (s->maxLen - 1) ? 1 : 0);
}

int stack_push(sqstack * s, data_t value)
{
    if(s == NULL) {
        printf("the stack is not exist\n");
        return -1;
    }

    if(s->top == (s->maxLen - 1))
    {
        printf("the stack is full\n");
        return -1;
    }

    s->top++;
    s->data[s->top] = value;

    return 0;
}

data_t stack_pop(sqstack * s)
{
    s->top--;
    return s->data[s->top+1];  
    
}





