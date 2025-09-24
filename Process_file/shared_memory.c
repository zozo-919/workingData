#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // step1 创建一个共享对象. 这是一套固定的流程

#if 1
    char *fileNm = "/shareFile";
#else
    // char fileNm[100] ={0};
    // sprintf(fileNm,"/shareFile%d",getpid()); 
#endif

    /**
     * int shm_open(const char * _name, int _oflag, mode_t _mode);
     * @brief 
     * @param _name: 路径名称 以/开头\0结尾    
     *        _oflag: 打开模式 二进制可拼接
     *              （1）O_CREAT: 如不存在则创建新的共享内存对象
     *              （2）O_EXCL:  当与O_CREAT一起使用时 如果共享内存对象已存在 则返回错误（避免覆盖现有对象）
     *              （3）O_RDONLY: 以只读方式打开
     *              （4）O_RDWR: 以读写方式打开
     *              （5）O_TRUNC: 用于截断现有对象至0长度        
     *      _mode: 当创建共享内存对象时 使用的权限位 类似文件的权限模式 一般0644即可
     *                                      
     * @return 成功返回一个新的描述符 失败返回-1
     *  */
    int newFd = shm_open(fileNm, O_CREAT|O_RDWR, 0664);
    if (newFd < 0) {
        perror("shm_open fail");
        exit(EXIT_FAILURE);
    }

    /**
     * int ftruncate(int _fd, off_t length);
     * @brief 将指定文件描述符扩展或截取到指定大小
     * @param _fd ：文件描述符 需要打开并且有权限  length：指定长度 单位字节
     * @return 0 - 成功  -1 - 失败
     */
    // step2 设置共享内存大小
    ftruncate(newFd,1024);

    // step3 内存映射
    /**
     * void *  mmap(void * addr, size_t length, int port, int flags, int fd, off_t offset)；
     * @brief 将文件映射到内存区域 进程可以直接对内存区域进行读写操作 就像操作普通内存一样 但实际上是对文件或设备进行读写 从而实现高效的I/O操作
     * @param addr: 指向期望映射的内存起始地址的指针 通常设为NULL 让系统选合适的地址     
     *        length: 要映射的内存区域的长度 以字节为单位
     *        port: 内存映射区域的保护标志 可以是以下标志组合
     *          （1）PROT_READ: 允许读取映射区域
     *          （2）PROT_WRITE: 允许写入映射区域
     *          （3）PROT_EXEC: 允许执行映射区域
     *          （4）PROT_NONE: 页面不可访问
     *        flags: 映射选项标志
     *          （1）MAP_SHARED: 映射区是共享的 对映射区域的修改会影响文件和其他映射到同一区域的进程（一般使用共享）
     *          （2）MAP_PRIVATE: 映射区域是私有的 对映射区域的修改不会影响原始文件 对文件的修改会被暂时保存在一个私有副本中
     *          （3）MAP_ANONYMOUS: 创建一个匿名映射 不与任何文件关联
     *          （4）MAP_FIXED: 强制映射到指定的地址 如果不允许映射 将返回错误
     *        fd: 文件描述符 用于指定要映射的文件或设备 如果匿名映射 则传入无效的文件描述符（-1）
     *        offset: 从文件开头的偏移量 映射开始的位置 
     * @return 成功返回映射区域的起始地址 可以像普通内存那样使用该地址进行读写  失败返回（void*）-1 即MAP_FAILED
     */
    char *share = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED,newFd,0);
    if(share == MAP_FAILED) {
        perror("mmap fail");
        close(newFd);
        exit(1);
    }

    // step4  映射完成后 关闭fd连接（并非释放）
    close(newFd);

    // step5 使用内存映射 实现进程间的通讯
    pid_t pidnew = fork();
    if(0 > pidnew) {
        perror("");
        exit(1);
    } else if(pidnew == 0) {
        // 子进程
        strcpy(share, "you are good people\n");
        printf("%d finished the send\n",getpid());
    } else {
        // 父进程

        /* 等待子进程 */
        waitpid(pidnew, NULL, 0);

        printf("[%d] saved the %d letter:%s \n",getpid(),pidnew,share);

        // step6 释放映射区
        /**
         * int munmap(void *addr, size_t length)
         * @brief 用于取消之前通过 mmap（）函数建立的内存映射关系
         * @param addr: 指向之前通过mmap（）映射的内存区域起始地址的指针  length: 要解除关系的大小 与mmap映射的大小一致
         * @return 0 - 成功  -1 - 失败
         */
        munmap(share, 1024);
    }

    //step7 释放共享内存对象
    /**
     * int shm_unlink(const char* name);
     * @brief   删除一个有shm_open()创建的命名共享内存对象 
     * @param   name: 要删除的内存共享对象名称
     * @return  0 - 成功    -1 - 失败
     */
    shm_unlink(fileNm);
    
    return 0;
}
