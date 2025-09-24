#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>


int main(int argc, char const *argv[])
{
    char  *shmValName = "unnamed_sem_shm_value";
    // 创建信号量 -> 使用共享内存创建
    char *shmSemName = "unnamed_sem_shm_sem";

    // 创建共享内存对象
    int valFd = shm_open(shmValName,O_CREAT|O_RDWR,0666);
    int semFd = shm_open(shmSemName,O_CREAT|O_RDWR,0666);

    // 调整内存共享对象的大小
    ftruncate(valFd,sizeof(int));
    ftruncate(semFd, sizeof(sem_t));

    //将内存共享对象映射到共享内存区域
    int *value = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,valFd,0);
    // 将共享内存的信号量映射到共享内存区域
    sem_t *sem = mmap(NULL, sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED,semFd,0);

    // 初始化共享变量的值
    *value = 0;
    // 初始化信号量  进程间！！！！！！ sem_init的区别就在这里
    sem_init(&sem,1,1);

    int pid = fork();
    if(0 > pid) {
        perror("fork");
    }

    if(pid > 0) {
        // 父进程
        // 信号量等待
        sem_wait(&sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        // 信号量唤醒
        sem_post(&sem);

        // 等待子进程执行完毕 回收资源
        waitpid(pid,NULL,0);
    } else {
        // 子进程
        sem_wait(&sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        // 信号量唤醒
        sem_post(&sem);

    }

    if(pid > 0) {
        if (sem_destroy(&sem) == -1) {
            perror("sem destroy");
        }
    }

    // 解除共享内存映射 关闭描述符
    if (munmap(sem,sizeof(sem_t)) == -1) {
        perror("munmap sem");
    }

    if(close(semFd) == -1) {
        perror("sem close");
    }

    if(munmap(value, sizeof(int)) == -1) {
        perror("munmap value");
    }

    if(close(valFd) == -1) {
        perror("val close");
    }

    if(pid >0) {
        if(shm_unlink(shmValName) == -1) {
            perror("shmValName unlink");
        }

        if(shm_unlink(shmSemName) == -1) {
            perror("shmSemName unlink");
        }
    }

    return 0;
}
