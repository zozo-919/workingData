#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int fd = open("io123.txt",O_RDONLY);
    if(-1 == fd) {
        // perror 错误输出
        perror("open");
        exit(1);
    }

    char strBuf[1024];  //用于存放读取的数据
    ssize_t bytes_read;

    /**
     * ssize_t	 read(int _fd, void * _buf, size_t __nbyte)
     * @brief     读取文件的数据
     * @param   _fd: 文件描述符   _buf: 存放数据  __nbyte:读取数据的长度
     * @return  long int: 读取到的数据字节长度 成功>0  失败 -1
     */
    while((bytes_read = read(fd,strBuf,sizeof(strBuf))) > 0) {
        //文件描述符类型 0:stdin 1:stdout  2:stderr
        /**
         * ssize_t write(int __fd, const void *__buf, size_t __nbyte)
         * @brief 写数据
         * @param   __fd:文件描述符   __buf:要写出的数据  __nbyte:写出的数据长度
         * @return  成功返回写出数据的长度 失败返回-1
         */
        write(STDOUT_FILENO, strBuf, bytes_read);
    }

    if(-1 == bytes_read) {
        perror(" read ");
        /**
         * int close(int __fd)
         * @brief 关闭文件
         * @param   __fd: 文件描述符
         * @return  成功返回0 失败返回-1
         */
        close(fd);
        exit(1);
    }

    close(fd);
    
    return 0;
}
