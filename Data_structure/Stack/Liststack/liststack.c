
#include "liststack.h"


/*
 * @brief create a liststack
 * @param 
 * @return liststack
 **/
liststack stack_create()
{
    liststack s = (liststack)malloc(sizeof(listnote));
    if(s == NULL) {
        return NULL;
    }

    s->data = 0;
    s->next = NULL;

    return s;
}


/*
 * @brief push data into the  liststack
 * @param s   value -- into data
 * @return 0 -- success  -1 -- false
 **/
int stack_push(liststack s, data_t value)
{
    if(s == NULL)
        return -1;

    liststack p = (liststack)malloc(sizeof(listnote));
    if(p == NULL)
        return -1;

    p->data = value;
    p->next = s->next;
    s->next = p;

    return 0;

}


/*
 * @brief pop data from liststack
 * @param s
 * @return the data of pop
 **/
data_t stack_pop(liststack s)
{
    liststack p ;
    p = s->next;
    s->next = p->next;

    data_t tmp = p->data;
    
    free(p);
    p = NULL;

    return tmp;

}


/*
 * @brief cat the pop data of liststack
 * @param s
 * @return top data
 **/
data_t stack_top(liststack s)
{
    return s->next->data;
}

/*
 * @brief Is the liststack empty?
 * @param s
 * @return 1 -- empty. 0--not empty
 **/
int stack_empty(liststack s)
{
    if(s == NULL)
        return -1;

    return (s->next == NULL? 1 : 0);
}


/*
 * @brief free the liststack
 * @param s
 * @return 0 -- success  -1 -- false
 **/
int stack_free(liststack s)
{
    if(s == NULL)
        return -1;

    liststack p;
    while(s != NULL)
    {
        p = s;
        s = s->next;
        free(p);
        p = NULL;
    }

    return 0;
}