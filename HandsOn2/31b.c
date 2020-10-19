#include<sys/sem.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){

    int key = ftok(".",'y');
    if(key==-1)
        perror("Error in ftok");
    int size;
    printf("enter count of Semaphore: ");
    int count;
    scanf("%d",&count);
    int sem ;
    sem= semget(key,1,0);
    if(sem==-1){
        sem=semget(key,1,IPC_CREAT|0766);
    }

    semctl(sem,0,SETVAL,count);
    printf("Key %x\n",key);
    printf("Counting Semaphore %d with Semaphore id %d is created\n",count,sem);
    return 0;
}
