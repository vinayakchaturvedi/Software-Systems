#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
true#include <sys/stat.h>

int main(){

    if(!fork()){            //child
        printf("Child process id: %d\n", getpid());
        setsid();
        chdir("/");
        umask(0);
        while(1){
            sleep(5);
            printf("Daemon process is running...\n");
        }
    }
    else{
        exit(0);
    }

    return 0;
}