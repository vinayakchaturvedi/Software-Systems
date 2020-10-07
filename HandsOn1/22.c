#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    int fd = open("MainFileQues22.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
    int childId = fork();
    char content[61];
    if(childId){    //parent
        write(fd, "Writing from parent process...\n", 31);
        wait(NULL);
        lseek(fd, 0, SEEK_SET);
        read(fd, content, sizeof(content));
        write(2, content, sizeof(content));             //Displaying content on the STDOUT
        close(fd);
    }
    else{           //child
        write(fd, "Writing from child process...\n", 30);
        close(fd);
        exit(0);
    }

    return 0;
}
/*
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cc 22.c
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ./a.out
Writing from parent process...
Writing from child process...
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cat MainFileQues22.txt
Writing from parent process...
Writing from child process...
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$
*/