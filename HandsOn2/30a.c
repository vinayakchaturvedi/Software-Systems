#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){

    int key = ftok(".",'z');
    if(key==-1)
        perror("Error in ftok");
    int size;
    printf("Enter size of memory\n");
    scanf("%d",&size);
    int shm = shmget(key,size,IPC_CREAT|0744);
    if(shm==-1)
        perror("Error in msgget");
    printf("Key %x\n",key);
    printf("SHM_id %d of size %d is created\n",shm,size);

    char *data;
    data = shmat(shm,NULL,0);

    printf("Write some data to shared memory segment\n");
    getchar();
    fgets(data,1024,stdin);
    printf("Reading from shared memory segment: %s",data);

    return 0;
}
