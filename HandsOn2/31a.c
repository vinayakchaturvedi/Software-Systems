#include<sys/sem.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){

    int key = ftok(".",'z');
    if(key==-1)
        perror("Error in ftok");
    int size;
    int sem = semget(key,1,IPC_CREAT|0744);
    semctl(sem,0,SETVAL,1);
    if(sem==-1)
        perror("Error in semget");
    printf("Key %x\n",key);
    printf("Binary Semaphore with Semaphore id %d is created\n",sem);

    return 0;
}
