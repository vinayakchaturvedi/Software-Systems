#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){

    int key = ftok(".",'z');
    if(key==-1)
        perror("Error in ftok");

    int msgq = msgget(key,IPC_CREAT|IPC_EXCL|0744);

    if(msgq==-1)
        perror("Error in msgget");


    printf("Key: %x\n",key);
    printf("Message queue id: %d\n",msgq);


return 0;
}
