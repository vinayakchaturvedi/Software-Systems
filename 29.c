#include<stdio.h>
#include<sched.h>
#include<unistd.h>

int main(){

    int currentPolicy = sched_getscheduler(getpid());
    printf("Current policy is: %d\n", currentPolicy);

    struct sched_param scp;
    scp.sched_priority = 1;
    if(sched_setscheduler(getpid(), SCHED_FIFO, &scp) != -1){
        int updatedPolicy = sched_getscheduler(getpid());
        printf("Updated policy is: %d\n", updatedPolicy);
    }
    else{
        perror("Error");
    }
    return 0;
}