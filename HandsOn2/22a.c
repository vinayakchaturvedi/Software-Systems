#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
extern int errno;
int main(){

    printf("Opening FIFO in write only mode\n");
    int fd = open("myfifo",O_WRONLY);
    if (fd==-1)
    {
        perror("Error occured during open call\n");
        return 0;
    }
    char buf[100];
    fgets(buf,100,stdin);
    write(fd,buf,strlen(buf));
    close(fd);


return 0;	
}

