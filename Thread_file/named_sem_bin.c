#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    char  *shmValName = "/unnamed_sem_shm_value";
    char * sem_name = "/named_sem_shm";

    // 创建共享内存对象
    int valFd = shm_open(shmValName,O_CREAT|O_RDWR,0666);

    /**
     * sem_t *sem_open(const char*name,int oflag,mode_t mode, unsigned int value);
     * @brief 创建或打开一个命名信号量
     * @param name:以/开头 且不包含其他/
     *        oflag: 打开标志
     *          （1）O_CREAT
     *          （2）O_EXCL
     *        mode: 权限设置 如0664
     *        value: 信号量初始值
     * @return 成功返回信号量指针  失败返回SEM_FAILED
     */
    sem_t *sem = sem_open(sem_name,O_CREAT,0666,1);
    if(sem == SEM_FAILED) {
        perror("sem_open failed");
    }

    // 调整内存共享对象的大小
    ftruncate(valFd, sizeof(int));

    //将内存共享对象映射到共享内存区域
    int *value = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,valFd,0);

    // 初始化共享变量的值
    *value = 0;

    int pid = fork();
    if(0 > pid) {
        perror("fork");
    }

    if(pid > 0) {
        // 父进程
        // 信号量等待
        sem_wait(&sem);
        int tmp = *value + 1;
        *value = tmp;
        // 信号量唤醒
        sem_post(&sem);

        // 等待子进程执行完毕 回收资源
        waitpid(pid,NULL,0);
        printf("the final value is%d\n",*value);
    } else {
        // 子进程
        sem_wait(&sem);
        int tmp = *value + 1;
        *value = tmp;
        // 信号量唤醒
        sem_post(&sem);

    }

    // 解除共享内存映射 关闭描述符
    if(munmap(value, sizeof(int)) == -1) {
        perror("munmap value");
    }

    /**
     * int sem_close(sem_t *sem);
     * @brief 关闭一个已打开的命名信号量
     * @param sem : 要关闭的信号量指针
     * @return 0-成功  -1 - 失败
     */
    if(sem_close(sem) == -1) {
        perror("sem_close");
    }

    if(close(valFd) == -1) {
        perror("val close");
    }

    if(pid > 0) {
        if(shm_unlink(shmValName) == -1) {
            perror("shmValName unlink");
        }

        /**
         * int sem_unlink(const char *name);
         * @brief 删除一个有名信号量
         * @param name ：要删除的；信号量名称
         * @return 0 - 成功  -1 - 失败 
         */
        if (sem_unlink(sem_name) == -1) {
            perror("sem unlink");
        }
    }

    return 0;
}
