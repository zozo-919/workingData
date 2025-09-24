#ifndef LINKLIST_H
#define LINKLIST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int data_t;

typedef struct node
{
    data_t data;
    struct node * next;
    
}linknode, *linklist;

linklist list_create(void);

int list_tail_insert(linklist H, data_t val);

void list_show(linklist H);

linklist list_search(linklist H, int pos);

int list_insert(linklist H, int pos, data_t value);

int list_delete(linklist H, int pos);

int list_free(linklist H);

int list_reverse(linklist H);

linklist list_maxsum(linklist H , data_t * value);

int list_merge(linklist H1, linklist H2);




#endif /* LINKLIST_H */