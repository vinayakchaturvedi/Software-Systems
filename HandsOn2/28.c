#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){

    int key = ftok(".",'z');
    if(key==-1)
        perror("Error in ftok");

    int msgq = msgget(key,0);

    if(msgq==-1)
        perror("Error in msgget");

    struct msqid_ds ds;
    //read values in ds
    int ret = msgctl(msgq,IPC_STAT,&ds);
    if(ret==-1)
        perror("Error in msgctl");
    printf(" Before updating: Permissions 0%o\n",ds.msg_perm.mode);
    int p;
    //new permissions
    printf("Enter new permissions\n");
    scanf("%o",&p);
    ds.msg_perm.mode = p;
    //setting permission
    ret = msgctl(msgq,IPC_SET,&ds);
    if(ret==-1)
        perror("Error in msgctl");
    printf("After updating Permissions 0%o\n",ds.msg_perm.mode);


    return 0;
}
