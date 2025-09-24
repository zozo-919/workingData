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
     * @brief   从文件流中读取数据
     * @param   ptr:    指向存储数据的缓冲区指针。读取的数据将存放在这里
     *          size:   每个数据项的字节大小。通常是 sizeof(数据类型)
     *          nmemb:  要读取的数据项数量
     *          stream: 文件指针，指向要读取的文件流
     * @return  成功读取的完整数据项数量（不是字节数！）
     */
    size_t items_read = fread(numbers, sizeof(int), 10, fp);    /* 尝试读取10个int，每个sizeof(int)字节 */
    
    printf("read [%zu] \n", items_read);
    
    fclose(fp);
    return 0;
}