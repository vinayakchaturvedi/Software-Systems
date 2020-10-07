#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("SIGINT has been caught with number: %d\n", sig);
    exit(1);
}

int main(){

    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
    printf("Waiting for SIGINT...\n");
    sleep(5);
    printf("No SIGINT within 5 seconds\n");

    return 0;
}
