#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){

    int fd = open("MainFileQues22.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int childId = fork();
    if(childId){    //parent
        write(fd, "Writing from parent process...\n", 31);
    }
    else{           //child
        write(fd, "Writing from child process...\n", 30);
    }

    return 0;
}