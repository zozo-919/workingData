#include "tree.h"

bitree * tree_create(void)
{
    data_t inputCh;
    scanf("%c ",&inputCh);
    if(inputCh == '#')
        return NULL;
    
    bitree *r = (bitree*)malloc(sizeof(bitree));
    if(r == NULL) {
        printf(" malloc r failed\n");
        return NULL;
    }
    
    r->data = inputCh;
    r->lchild = tree_create();
    r->rchild = tree_create();
}

//先序
void preorder(bitree * r)
{
    if(r == NULL) {
        return;
    }
    printf("%c\n",r->data);
    preorder(r->lchild);
    preorder(r->rchild);
}

//中序
void inorder(bitree *r )
{
    if(r == NULL)
        return;
    
    inorder(r->lchild);
    printf("%c\n",r->data);
    inorder(r->rchild);
}

//后序
void postorder(bitree * r)
{
    if(r == NULL)
        return;
    
    preorder(r->lchild);
    preorder(r->rchild);
    printf("%c\n",r->data);
}

