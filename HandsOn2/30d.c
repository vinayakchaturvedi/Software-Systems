#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){
    int shm;
    printf("Enter Id  of shared  memory\n");
    scanf("%d",&shm);

    int ret = shmctl(shm,IPC_RMID,NULL);
    if(ret==-1)
        perror("error at shmtctl");
    else
        printf("Shared memory Removed\n");
    return 0;
}
