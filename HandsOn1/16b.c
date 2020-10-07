#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd = open("MainFileQues16.txt", O_CREAT|O_RDONLY, 0644);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Implementing read lock. Before entering critical section.\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Inside Critical section...\n");

    printf("Press enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Read lock Unlocked Now...\n");

    close(fd);
    return 0;
}