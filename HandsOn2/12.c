#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(){

    if(!fork()){        //Child
        printf("Parent id before killing parent: %d\n", getppid());
        kill(getppid(), SIGKILL);
        sleep(2);
        printf("Parent id after killing (Should be orphan now): %d\n", getppid());
        exit(0);
    }
    else{       //Parent
        sleep(1);
        printf("I am still alive after 5 seconds...\n");
    }

    return 0;
}
