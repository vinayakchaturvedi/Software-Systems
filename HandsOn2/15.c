#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd[2];
    pipe(fd);
    char buff1[50], buff2[50];

    if(!fork()){            //child
        close(fd[1]);       //closing write end
        read(fd[0], buff2, sizeof(buff2));          //read content from parent via pipe
        printf("Message from parent: %s\n", buff2);
        close(fd[0]);
    }
    else{                       //parent
        close(fd[0]);           //closing read end
        printf("Enter the message that you want to send to child: ");
        scanf("%[^\n]", buff1);
        write(fd[1], buff1, sizeof(buff1));         //writing to child via pipe
        close(fd[1]);
    }
    return 0;
}