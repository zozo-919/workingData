#include "sqstack.h"


/*
 * @brief create a sqstack
 * @param len -- the sqstack maxlen
 * @return sqstack
 **/
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


/*
 * @brief push data into the sqstack
 * @param s -- the sqstack  value -- into the data
 * @return 0-- success -1 --false
 **/
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

/*
 * @brief pop the data of sqstack
 * @param s 
 * @return pop data
 **/
data_t stack_pop(sqstack * s)
{
    s->top--;
    return s->data[s->top+1];  
    
}

/*
 * @brief cat the top data of the  sqstack
 * @param s
 * @return sqstack
 **/
data_t stack_top(sqstack *s)
{
    return s->data[s->top];
}

/*
 * @brief clear a sqstack
 * @param s
 * @return 0 --success -1 --false
 **/
int stack_clear(sqstack *s)
{
    if(s == NULL)
    {
        return -1;
    }

    s->top = -1;
    return 0;
    
}


/*
 * @brief free the sqstack
 * @param s
 * @return 0 -- success  -1 -- false
 **/
int stack_free(sqstack *s)
{
    if(s == NULL)
    {
        return -1;
    }

    if(s->data != NULL) {
        free(s->data);
        s->data = NULL;
    }
    
    free(s);
    s = NULL;

    return 0;
}

/*
 * @brief Is the sqstack empty?
 * @param s
 * @return 1 -- empty  0 -- not empty
 **/
int stack_empty(sqstack *s)
{
    if(s == NULL) {
        printf("the stack is not exist\n");
        return 0;
    }

    return (s->top == -1 ? 1 : 0);
    
}


/*
 * @brief Is the sqstack full?
 * @param s
 * @return 1 -- full  0--not full
 **/
int stack_full(sqstack *s)
{
    if(s == NULL) {
        printf("the stack is not exist\n");
        return -1;
    }

    return (s->top == (s->maxLen - 1) ? 1 : 0);
}