#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
struct msgbuf{

    long mtype;
    char mtext[100];

};

int main(){

    int key = ftok(".",'z');
    if(key==-1)
        perror("Error in ftok");

    int msgq = msgget(key,0);

    if(msgq==-1)
        perror("Error in msgget");

    struct msgbuf msg;
    printf("Enter type of msg\n");
    scanf("%ld",&msg.mtype);

    int ret = msgrcv(msgq,&msg,sizeof(msg),msg.mtype,0);
    if(ret==-1)
        perror("Error in msgctl");
    else
        printf("%s",msg.mtext);

    return 0;
}
