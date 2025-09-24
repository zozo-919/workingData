/**
 * @file    fwrite_test.c
 * @author  Zozo@
 * @brief   Description
 * @version 1.0
 * @date    2025-08-30
 */


 #include <stdio.h>

int main() 
{
    FILE *fp = fopen("io1.txt", "r+");
    if (!fp) {
        perror("fopen failed");
        return 1;
    }
    
    int numbers[] = {1, 2, 3, 4, 5};
    /**
     * size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
     * @brief   ����������д��
     * @param   ptr:    ָ��Ҫд�����ݵĻ�����ָ��
     *          size:   ÿ����������ֽڴ�С
     *          nmemb:  Ҫд�������������
     *          stream: �ļ�ָ�룬ָ��Ҫд����ļ���
     * @return  �ɹ�д��������������������ֽ�������
     */
    size_t items_written = fwrite(numbers, sizeof(int), 5, fp);
    printf("fwrite [%zu] success! \n", items_written);

    fclose(fp);
    return 0;
}