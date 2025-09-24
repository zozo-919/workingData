#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char data_t;

typedef struct node_t {
    data_t data;
    struct node_t * lchild, *rchild;
}bitree;

bitree * tree_create(void);
void preorder(bitree * r);
void inorder(bitree *r );
void postorder(bitree * r);





#endif  /* TREE_H */