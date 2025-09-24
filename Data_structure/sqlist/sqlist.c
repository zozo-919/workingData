#include <stdio.h>
#include "sqlist.h"
#include <stdlib.h>
#include <string.h>

/*
 * @brief: Creat a sqlist
 * @param : void
 * @ret   : a new sqlist
 **/
sqlink list_create(void){

	// 创建顺序表结构体 并为之分配空间
	sqlink L = (sqlink)malloc(sizeof(sqlist));
	if(L == NULL){
		printf("list malloc failed\n");
		return L;
	}
	
	// 初始化顺序表
	memset(L, 0, sizeof(sqlist));
	L->last = -1;

	return L;
}



/*
 * @brief : Clear the sqlist
 * @param : L-- The sqlist needs to be cleared
 * @ret   : -1--false  0--true
 **/
int list_clear(sqlink L){
	if(L == NULL)
		return -1;
	memset(L,0,sizeof(sqlist));
	L->last = -1;
	
	return 0;
}

/*
 * @brief  : Is list empty?
 * @param  : L -- sqlist 
 * @ret    : 1--empty  0--not empty
 **/
int list_empty(sqlink L)
{
	if(L->last == -1)
		return 1;

	return 0;
	
}

/*
 * @brief : The length of The sqlist
 * @param  : L list
 * @ret    : the list length
 **/
int list_length(sqlink L)
{
	if(L == NULL)
		return -1;
	return (L->last+1);
}


/*
 * @brief : Search for a val
 * @param  : L--list  val--need search value
 * @ret    :  -1--not exist
 **/
int list_locate(sqlink L, data_t val)
{
	if(L == NULL) {
		printf("sqlist is not exsit\n");
		return -1;
	}

	for(int i = 0; i <= L->last; i++)
	{
		if(val == L->data[i])
		{
			printf("pos = %d\n",i);
			return i;
		}
	}

	return -1;

}

/*
 * @brief : Insert data into a sqlist
 * @param : L--sqlist val--need inserted value  pos--need inserted pos
 * @ret    : the list length
 **/
int list_insert(sqlink L, data_t val, int pos)
{
	if(L->last == MAX_SIZEN -1) {
		printf("the list is full\n");
		return -1;
	}

	if(pos < 0 || pos > L->last) {
		printf("the pos if invalid\n");
		return -1;
	}

	for(int i=L->last; i>=pos; i--)
	{
		L->data[i+1] = L->data[i];
	}

	L->data[pos] = val;
	L->last++;

	return 0;
}

/*
 * @brief : Traverse the sqlist
 * @param : L--sqlist 
 * @ret
 **/
void list_show(sqlink L)
{
	if(L == NULL) {
		printf("This sqlink is not exist\n");
		return;
	}

	for(int i=0; i < L->last+1; i++)
	{
		printf("data[%d] = [%d]\n",i, L->data[i]);
	}
}


/*
 * @brief : Free the sqlist
 * @param : L--sqlist 
 * @ret.  : 0--true -1--false
 **/
int list_free(sqlink L)
{
	if(L == NULL)
		return -1;
	
	free(L);
	L = NULL;
	return 0;
}


/*
 * @brief : Delete the data at a position in he sqlist
 * @param : L--sqlist pos--the data pos
 * @ret.  : 0--success -1--fail
 **/
int list_delete(sqlink L, int pos)
{
	if(L == NULL || pos < 0 || pos > L->last || L->last < 0)
		return -1;

	for(int i = pos; i < L->last; i++)
	{
		L->data[i] = L->data[i+1];
	}

	L->last--;
	return 0;
	
}



/*
 * @brief : Merge two sqlist.   L2 to L1
 * @param : L1 L2--sqlist 
 * @ret.  : 0--true -1--false
 **/
int list_merge(sqlink L1, sqlink L2)
{
	if(L1 == NULL || L2 == NULL)
			return -1;
	
#if 1
	
	for(int i = 0; i<= L2->last; i++)
	{
		for(int j=0; j<=L1->last; j++)
		{
			if(((L2->data[i]) == (L1->data[j])))
				break;
		}

		if(L1->last+1 > MAX_SIZEN)
			return -1;
		
		L1->data[L1->last+1] = L2->data[i];
		L1->last++;
	}

#else

	int pos1 = 0;
	while(pos1 <= L2->last)
	{
		int ret = list_locate(L1, L2->data[pos1]);
		if(ret == -1)
		{
			if(list_insert(L1, L2->data[pos1], L1->last+1) == -1)
				return -1	;
		}
		pos1++;
	}

#endif

	return 0;
}


int list_purge(sqlink L)
{
	int i=1,j=0;

	if(L->last == 0)
		return 0;

	while (i <= L->last)
	{
		j = i-1;
		while (j>=0)
		{
			if(L->data[i] == L->data[j])
			{
				list_delete(L,i);
				break;
			} else {
				j--;
			}
		}

		if(j < 0)
		{
			i++;
		}
		
	}
	
	return 0;

}
