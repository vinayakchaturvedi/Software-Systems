#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd = open("MainFileQues16.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Implementing write lock. Before entering critical section.\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Inside Critical section...\n");

    char content[] = "Adding content from critical section...";
    write(fd, content, sizeof(content) - 1);

    printf("Press enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Write lock Unlocked Now...\n");

    close(fd);
    return 0;
}