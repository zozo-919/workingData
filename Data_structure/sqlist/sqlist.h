
#ifndef SQLIST_H
#define SQLIST_H

#define MAX_SIZEN 100	// ����˳�����������

typedef int data_t;

typedef struct{
	data_t data[MAX_SIZEN];		// ��̬����洢Ԫ��
	int last;					// ��ǰ˳������һ��Ԫ�ص��±� �� ������-1
}sqlist,*sqlink;				// sqlist - ˳���ṹ��	sqlink - �ṹ��ָ��	

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
