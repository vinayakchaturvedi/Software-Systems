#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main(){

    //create orphan -- parent is killed or done but child still running

    int childId = fork();
    if(childId){        //parent
        printf("Parent running with pid: %d: \n", getpid());
        sleep(1);
        printf("This is Parent and my processing is done\n");
    }
    else{               //child
        printf("Child running with pid: %d: and parent pid: %d\n", getpid(), getppid());
        sleep(5);
        printf("This is child with parent id: %d and going to terminate now\n", getppid());
        exit(0);
    }

    return 0;
}