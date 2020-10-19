#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){


    printf("Maximum number of files that can be opened: %ld\n",sysconf(_SC_OPEN_MAX));

    int fd = open("myfifo",O_RDWR);
    printf("Max buffer size of Pipe: %ld\n",fpathconf(fd,_PC_PIPE_BUF));

}
