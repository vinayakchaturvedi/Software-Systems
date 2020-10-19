#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){


    struct msqid_ds ds;
    //read values in ds
    int msgq;
    printf("Enter Message queue to be removed\n");
    scanf("%d",&msgq);
    int ret = msgctl(msgq,IPC_STAT,&ds);
    if(ret==-1){
        perror("Error in msgctl");
        return 0;
    }
    //removing msg queue
    ret = msgctl(msgq,IPC_RMID,&ds);
    if(ret==-1){
        perror("Error in msgctl");
        return 0;
    }
    printf("Message queue with id %x removed\n",msgq);


    return 0;
}
