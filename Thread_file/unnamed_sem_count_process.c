#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    char *shmName = "unnamed_sem_shm";
    // 创建共享内存
    int fd = shm_open(shmName,O_CREAT | O_RDWR,0666);
    // 调整共享内存大小
    ftruncate(fd, sizeof(sem_t));
    // 映射
    sem_t *sem = mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    sem_init(sem, 1, 0);

    pid_t pid= fork();
    if(0 > pid) {
        perror("fork");
    } else if(0 == pid) {
        sleep(1);
        sem_post(sem);
    } else {
        sem_wait(sem);
        waitpid(pid,NULL,0);

        if(sem_destroy(sem) == -1) {
            perror("sem_destroy");
        }
    }

    if (munmap(sem,sizeof(sem_t)) == -1) {
        perror("munmap");
    }
    if (close(fd) == -1)
    {
        perror("close");
    }

    if (pid > 0 )
    {
        if(-1 == shm_unlink(shmName)) {
            perror("shm_numlink");
        }
    }

    return 0;
}
