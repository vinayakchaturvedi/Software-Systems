#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
extern int errno;
int main(){

    printf("Opening FIFO in write only mode\n");
    int fd = open("myfifo",O_WRONLY);
    if (fd==-1)
    {
        perror("Error occured during open call\n");
        return 0;
    }
    char buff[100];
    printf("Enter the message that you want to send: ");
    scanf(" %[^\n]", buff);
    write(fd,buff,100);
    close(fd);


return 0;	
}

