
#ifndef SQLIST_H
#define SQLIST_H

#define MAX_SIZEN 100	// 定义顺序表的最大容量

typedef int data_t;

typedef struct{
	data_t data[MAX_SIZEN];		// 静态数组存储元素
	int last;					// 当前顺序表最后一个元素的下标 即 ：长度-1
}sqlist,*sqlink;				// sqlist - 顺序表结构体	sqlink - 结构体指针	

sqlink list_creat();

int list_clear(sqlink L);

int list_empty(sqlink L);

int list_length(sqlink L);

int list_locate(sqlink L, data_t val);

int list_insert(sqlink L, data_t val, int pos);

void list_show(sqlink L);

int list_free(sqlink L);

int list_delete(sqlink L, int pos);

int list_merge(sqlink L1, sqlink L2);




#endif
