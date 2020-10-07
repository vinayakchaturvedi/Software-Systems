#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd[2];
    pipe(fd);

    if(!fork()){            //child
         close(1);          //close normal stdout;
         dup2(fd[1], 1);    //Will assign 1 as file descriptor which is stdout
         close(fd[0]);      //close the read end

         execl("/bin/ls", "ls", "-l", NULL);
         close(fd[1]);
    }
    else{                     //parent
        close(0);             //close normal stdin
        dup2(fd[0], 0);       //Will assign 0 as file descriptor which is stdin
        close(fd[1]);         //close the write end

        execl("/usr/bin/wc", "wc",NULL);
        close(fd[0]);
    }
    return 0;
}