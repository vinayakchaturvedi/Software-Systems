#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd1[2], fd2[2];
    pipe(fd1);          //Pipe 1 will be used for sending data from parent to child
    pipe(fd2);          //Pipe 2 will be used for sending data from child to parent

    if(!fork()){            //child
         char buff1[50], buff2[50];

         close(fd1[1]);      //close write end of pipe 1
         read(fd1[0], &buff1, sizeof(buff1));
         printf("(In child) Message from parent: %s\n", buff1);
         close(fd1[0]);

         close(fd2[0]);     //close read end of pipe 2
         printf("(In child) Enter the message that you to send to parent: ");
         scanf("%[^\n]", buff2);
         write(fd2[1], buff2, sizeof(buff2));
         close(fd2[1]);
    }
    else{                       //parent
         char buff1[50], buff2[50];

         close(fd1[0]);     //close read end of pipe 1
         printf("(In parent) Enter the message that you to send to child: ");
         scanf("%[^\n]", buff2);
         write(fd1[1], buff2, sizeof(buff2));
         close(fd1[1]);

         close(fd2[1]);      //close write end of pipe 2
         read(fd2[0], &buff1, sizeof(buff1));
         printf("(In parent) Message from child: %s\n", buff1);
         close(fd2[0]);
    }
    return 0;
}