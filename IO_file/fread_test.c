/**
 * @file    fread_test.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */

 #include <stdio.h>

int main(int argc, char const *argv[]) 
{
    FILE *fp = fopen("io.txt", "r");
    if (fp == NULL) {
        perror("fopen io.txt");
        return 1;
    }
    
    int numbers[10];
    /**
     * #include <stdio.h>
     * size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
     * @brief   ���ļ����ж�ȡ����
     * @param   ptr:    ָ��洢���ݵĻ�����ָ�롣��ȡ�����ݽ����������
     *          size:   ÿ����������ֽڴ�С��ͨ���� sizeof(��������)
     *          nmemb:  Ҫ��ȡ������������
     *          stream: �ļ�ָ�룬ָ��Ҫ��ȡ���ļ���
     * @return  �ɹ���ȡ�����������������������ֽ�������
     */
    size_t items_read = fread(numbers, sizeof(int), 10, fp);    /* ���Զ�ȡ10��int��ÿ��sizeof(int)�ֽ� */
    
    printf("read [%zu] \n", items_read);
    
    fclose(fp);
    return 0;
}