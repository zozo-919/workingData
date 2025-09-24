

#include "linklist.h"

/*
 * @brief Create a new linklist
 * @param  void
 * @ret    new linklist
 **/
linklist list_create(void)
{
    linklist H = (linklist)malloc(sizeof(linknode));
    if (H == NULL)
    {
        printf("Create linklist fail\n");
        return H;
    }

    // memset(H, 0 ,sizeof(linknode));
    H->data = 0;
    H->next = NULL;
    return H;
    
}

/*
 * @brief Insert data at the end of the linklist
 * @param  H -- linklist  val -- insert value
 * @ret    0 -- success  -1 -- false
 **/
int list_tail_insert(linklist H, data_t val)
{
    linklist p;
    linklist q = H;

    if((p = (linklist)malloc(sizeof(linknode))) == NULL)
    {
        printf("malloc fail\n");
        return -1;
    }

    p->next = NULL;
    p->data = val;

    while (q->next != NULL)
    {
        q=q->next;
    }
    
    q->next = p;

    return 0;


}


/*
 * @brief Traverse the linklist
 * @param  H -- linklist
 * @ret    void
 **/
void list_show(linklist H)
{
    if (H == NULL)
    {
        printf("The linklist is not exist");
        return;
    }

    linklist p = H;

    while (p->next != NULL)
    {
        printf("data = [%d]\n",p->next->data);
        p = p->next;
    }

    // return 0;
    
}


/*
 * @brief Search for the node at the specified location
 * @param  H   pos 
 * @ret    searched linklist
 **/
linklist list_search(linklist H, int pos)
{
    if(H == NULL || pos == -1) {
        printf("H IS NULL\n");
        return H;
    }

    if(pos == -1) {
        return H;
    }

    if(pos < -1)
    {
        return NULL;
    }

    linklist p = H;   

    int i=0;  // -1 是head的pos 所以这里要pos+1
    while (i < pos+1)
    {
        p = p->next;
        if(p == NULL)
        {
            printf("pos is invalid\n");
            return NULL;
        }
        i++;
    }

    return p;
    
}


/*
 * @brief Insert a new node into the linklist
 * @param  H -- new linklist  pos -- want to insert pos  value -- want to insert value
 * @ret    0 -- success  -1 false
 **/
int list_insert(linklist H, int pos, data_t value)
{
    // 找到要插入的位置的前一个节点
    linklist p = list_search(H, pos-1);
    if(p == NULL)
        return -1;

    // 引入新的节点
    linklist q = (linklist)malloc(sizeof(linknode));
    if(q == NULL)
        return -1;
    
    // 赋值
    q->data = value;
    q->next = NULL;

    // 重新连接节点
    q->next = p->next;
    p->next = q;

    return 0;
}



/*
 * @brief Delete a node 
 * @param  H  pos
 * @ret    0 -- success  -1 false
 **/
int list_delete(linklist H, int pos)
{
    linklist p = list_search(H, pos-1);
    if(p == NULL)
    {
        return -1;
    }

    if(p->next == NULL)
    {
        printf("delete pos is invalid\n");
        return -1;
    }

    linklist q = p->next;
    p->next = q->next;

    free(q);
    q = NULL;

    return 0;

}


/*
 * @brief free the linklist 
 * @param  H
 * @ret    0 -- success  -1 false
 **/
int list_free(linklist H)
{
    if(H == NULL)
        return -1;

    linklist p = H; 

    while(H != NULL)
    {
        p = H;
        H = H->next;
        free(p);
    }

    return 0;
    
}

/*
 * @brief REVERSE THE LINKLIST 
 * @param  H  
 * @ret    0 -- success  -1 false
 **/
int list_reverse(linklist H)
{
    if(H == NULL)
    {
        return -1;
    }

    if(H->next == NULL || H->next->next == NULL)
    {
        return 0;
    }

    linklist p = H->next->next;

    H->next->next = NULL;

    linklist q ;

    while( p != NULL) {
        q = p;
        p = p->next;

        q->next = H->next;
        H->next = q;
    }

    return 0;
}


/*
 * @brief Find the node whose sum of data stored in two adjacent notes is the largest  
 * @param  H -- linklist  *value -- maximum sum  
 * @ret    the sought note
 **/
linklist list_maxsum(linklist H , data_t * value)
{
    if(H == NULL) {
        return NULL;
    }

    
    if (H->next == NULL || H->next->next == NULL || H->next->next->next == NULL) {
        printf("DONT NEED sum\n");
        return H;
    }

    linklist p = H->next;
    linklist q = H->next->next;
    linklist temp = H->next;
    data_t sum = p->data + q->data;;

    while(q->next != NULL) {
        p=q;
        q=q->next;

        if((p->data + q->data) > sum) {
            sum = p->data + q->data;
            temp = p;
            
        }

    }

    *value = sum;

    return temp;
    
}

/*
 * @brief Merge two linked lists in ascending order  
 * @param    
 * @ret    0 -- success  -1 -- false
 **/
int list_merge(linklist H1, linklist H2)
{

    if(H1 == NULL || H2 == NULL)
    {
        return -1;
    }

    linklist p, q, r;
    p = H1->next;
    q = H2->next;
    r = H1;

    H2->next = NULL;

    H1->next = NULL;

    while(p && q) {
        if(p->data < q->data)
        {
            r->next = p;
            p = p->next;
            r = r->next;
            r->next = NULL;
        } else {
            r->next = q;
            q = q->next;
            r = r->next;
            r->next = NULL;
        }
        
    }

    if(p == NULL)
    {
        r->next = q;
    } else {
        r->next = p;
    }

    return 0;
}