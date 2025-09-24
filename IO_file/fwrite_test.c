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
     * @brief   二进制数据写入
     * @param   ptr:    指向要写入数据的缓冲区指针
     *          size:   每个数据项的字节大小
     *          nmemb:  要写入的数据项数量
     *          stream: 文件指针，指向要写入的文件流
     * @return  成功写入的数据项数量（不是字节数！）
     */
    size_t items_written = fwrite(numbers, sizeof(int), 5, fp);
    printf("fwrite [%zu] success! \n", items_written);

    fclose(fp);
    return 0;
}