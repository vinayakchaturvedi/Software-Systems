#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd[2];
    pipe(fd);

    write(fd[1], "Hello World!\0", 13);

    char buff[13];
    read(fd[0], buff, sizeof(buff));
    printf("Content in pipe: %s\n", buff);
    close(fd[0]);
    close(fd[1]);

    return 0;
}