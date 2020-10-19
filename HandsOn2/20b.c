#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
extern int errno;
int main(){

    printf("Reading FIFO in readonly mode\n");
    int fd = open("myfifo",O_RDONLY);
    if (fd==-1)
    {
        perror("Error occured during open call\n");
        return 0;
    }

    char buf[100];
    read(fd,buf,sizeof(buf));
    printf("Message from source: %s\n",buf);

    close(fd);


return 0;	
}

