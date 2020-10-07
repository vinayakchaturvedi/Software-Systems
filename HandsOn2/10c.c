#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("SIGFPE has been caught with number: %d\n", sig);
    exit(1);
}

int main(){

    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;

    sigaction(SIGFPE, &action, NULL);
    printf("Creating floating point exception.\n");
    int a =1, b = 0;
    int c = a/b;

    return 0;
}
