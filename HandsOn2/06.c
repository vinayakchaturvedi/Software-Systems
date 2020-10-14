#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

void *connectionHandler(void *i){
    printf("Inside Thread.\n");
    return 0;
}

int main(){

    pthread_t threads;
    for(int i = 0; i < 3; i++){
        if(pthread_create(&threads, NULL, connectionHandler, NULL) < 0){
            perror("Not able to create thread");
            return 1;
        }
        printf("Running thread %d\n", i);
    }
    pthread_exit(NULL);

    return 0;
}
