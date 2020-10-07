#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("SIGFPE has been caught with number: %d\n", sig);
    exit(0);
}

int main(){

    signal(SIGFPE, handler);
    printf("Creating Floating point exception.\n");

    int a = 1, b = 0;
    int c = a/b;

    return 0;
}
