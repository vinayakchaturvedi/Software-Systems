#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

void *connectionHandler(void *i){
    int threadNumber  = *(int*)i;

    printf("Thread number: %d with thread Id: %ld\n", *(int*)i, pthread_self());
    return 0;
}

int main(){
    pthread_t threads;
    for(int i = 0; i < 3; i++){
        if(pthread_create(&threads, NULL, connectionHandler, (void*) &i) < 0){
            perror("Not able to create thread");
            return 1;
        }
    }
    pthread_exit(NULL);

    return 0;
}
