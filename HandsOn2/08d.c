#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

void handler(int sig){
    printf("SIGALRM has been caught with number: %d\n", sig);
}

int main(){

    signal(SIGALRM, handler);
    printf("Creating Alarm.\n");

    alarm(1);   //schedule alarm for 1 second.

    pause();    //Do not proceed until signal is handled.

    return 0;
}
