#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("\nSIGINT has been caught with number: %d\n", sig);
    exit(0);
}

int main(){

    signal(SIGINT, handler);
    printf("Waiting for Interrupt from keyboard.\n");
    sleep(3);
    printf("No SIGINT within 3 seconds\n");

    return 0;
}
