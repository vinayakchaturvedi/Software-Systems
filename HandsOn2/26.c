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
    printf("Enter type of msg: \n");
    scanf("%ld",&msg.mtype);
    printf("Enter message that you want to send: \n");
    getchar();
    scanf("%[^\n]", msg.mtext);

    printf("Entered Message is: %s\n",msg.mtext);
    int ret = msgsnd(msgq,&msg,sizeof(msg),0);
    if(ret==-1)
        perror("Error in msgctl");


    return 0;
}

/*
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn/handsonlist2$ cc 26.c
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn/handsonlist2$ ./a.out
Enter type of msg:
3
Enter message that you want to send:
This is Vinayak
Entered Message is: This is Vinayak
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn/handsonlist2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x7a0618f3 3          vinayak    744        112          1

vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn/handsonlist2$

*/