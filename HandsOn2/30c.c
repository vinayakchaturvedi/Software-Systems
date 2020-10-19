#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>

int main(){
    int shm;
    printf("Enter Id of shared  memory\n");
    scanf("%d",&shm);

    char *data;
    data = shmat(shm,NULL,SHM_RDONLY);
    printf("Reading from shared memory segment: %s\n",data);
    int ret = shmdt(data);
    if(ret==-1)
        perror("Error at shmdt");
    else
        printf("Shared Memory Detached\n");
    return 0;
}
