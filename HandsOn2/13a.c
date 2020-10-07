#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("SIGSTOP has been caught with number: %d\n", sig);
    exit(0);
}

int main(){

    signal(SIGSTOP, handler);
    printf("Process Id: %d\n", getpid());
    printf("Waiting for the catch SIGSTOP...\n");
    sleep(20);
    printf("Not able to caught.\n");      //SIGSTOP cannot be caught

    return 0;
}