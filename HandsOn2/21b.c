#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
extern int errno;
int main(){

    while(1)
    {
        char buf[100];
        char buf2[100];

        int fd = open("myfifo",O_WRONLY);
        if (fd==-1)
        {
            perror("Error occured during open call\n");
            return 0;
        }
        fgets(buf,100,stdin);
        write(fd,buf,100);
        close(fd);

        fd = open("myfifo",O_RDONLY);
        if (fd==-1)
        {
            perror("Error occured during open call\n");
            return 0;
        }
        read(fd,buf2,sizeof(buf2));
        printf(" User2: %s",buf2);
        close(fd);
    }


return 0;	
}

