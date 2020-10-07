#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd[2];
    pipe(fd);

    if(!fork()){            //child
         close(1);          //close normal stdout;
         fd[1] = fcntl(fd[1], F_DUPFD, 1);        //Will get and assign the least available file descriptor (greater than or equal to 1) which is stdout
         close(fd[0]);      //close the read end

         execl("/bin/ls", "ls", "-l", NULL);
         close(fd[1]);
    }
    else{                     //parent
        close(0);             //close normal stdin
        fd[0] = fcntl(fd[0], F_DUPFD, 0);        //Will get the least available file descriptor (greater than or equal to 0) which is stdin
        close(fd[1]);         //close the write end

        execl("/usr/bin/wc", "wc",NULL);
        close(fd[0]);
    }
    return 0;
}