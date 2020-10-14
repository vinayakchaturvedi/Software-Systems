#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void signalHandler(){
    printf("SIGPROF has been caught...\n");
    printf("Timer is now stopped\n");
    exit(0);
}

int main(){
    signal(SIGPROF, signalHandler);
    struct timeval timeVal1 = {10, 10};
    struct timeval timeVal2 = {0, 0};

    //interval for periodic timer
    struct itimerval value; //sends the signal
    value.it_value = timeVal1;
    value.it_interval = timeVal2;

    int ret;

    printf("Starting Timer...\n");
    ret = setitimer(ITIMER_PROF, &value, NULL);  //Decrements for both when the process executes and when the system is
     //executing on behalf of process and trigger SIGPROF after expiration.
    sleep(5);
    while(1);
    return 0;
}
