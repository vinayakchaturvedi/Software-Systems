#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(){

    int pid;
    printf("Enter pid to which you want to send SIGSTOP signal: ");
    scanf("%d", &pid);
    printf("Sending SIGSTOP...\n");
    kill(pid, SIGSTOP);
    return 0;
}