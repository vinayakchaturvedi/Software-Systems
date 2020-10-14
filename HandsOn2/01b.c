#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void signalHandler(){
    printf("SIGVTALRM has been caught...\n");
    printf("Timer is now stopped\n");
    exit(0);
}

int main(){
    signal(SIGVTALRM, signalHandler);
    struct timeval timeVal1 = {10, 10};
    struct timeval timeVal2 = {0, 0};

    //interval for periodic timer
    struct itimerval value; //sends the signal
    value.it_value = timeVal1;
    value.it_interval = timeVal2;

    int ret;

    printf("Starting Timer...\n");
    ret = setitimer(ITIMER_VIRTUAL, &value, NULL);  //Decrement only when process is executing and trigger SIGVTALRM after expiration.
    sleep(5);
    while(1);
    return 0;
}
