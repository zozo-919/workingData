#include <stdio.h>

int main(int argc, char const *argv[])
{
    /**
     * @brief 打开文件
     * @param
     * char * __restrict __filename: 字符串 表示要打开的文件名称
     * __restrict __mode: 访问模式
     *          （1）r: 只读模式  如果没有文件则报错
     *          （2）w: 只写模式 如果文件存在清空文件 如果不存在则创建文件
     *          （3）a: 只追加模式 如果文件存在 在末尾追加写  如果不存在则创建文件
     *          （4）r+: 读写模式 文件必须存在 写入是从头一个一个覆盖
     *          （5）w+: 读写模式 如果文件存在则清空文件 如果不存在则创建文件
     *          （6）a+: 读追加写模式 如果文件存在 在末尾追加写  如果不存在则创建文件
     * @ret:
     *      FILE * 结构体指针 表示一个文件
     *      报错返回NULL
        FILE * fopen(const char * __restrict __filename, const char * __restrict __mode)
    */
    char * test_filename = "io.txt";
    FILE * ioFile = fopen(test_filename,"a+");
    if (ioFile == NULL)
    {
        printf("open io.txt failed\n");
        /* code */
    } else {
        printf("open success\n");
    }
    
    return 0;
}
