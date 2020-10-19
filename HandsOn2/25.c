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
    int ret = msgctl(msgq,IPC_STAT,&ds);
    if(ret==-1)
        perror("Error in msgctl");
    printf("Key                                             0%x\n",ds.msg_perm.__key);
    printf("Permissions                                     0%o\n",ds.msg_perm.mode);
    printf("UID                                             %d\n",ds.msg_perm.uid);
    printf("GID                                             %d\n",ds.msg_perm.gid);
    printf("Last Msg sent                                   %ld\n",ds.msg_stime);
    printf("Last Msg Received                               %ld\n",ds.msg_rtime);
    printf("Last Msg Changed                                %ld\n",ds.msg_ctime);
    printf("CurrentSize                                     %ld\n",ds.__msg_cbytes);
    printf("Number of Messages                              %lu\n",ds.msg_qnum);
    printf("Maximum bytes allowed                           %lu\n",ds.msg_qbytes);
    printf("Last Msg sent PID                               %d\n",ds.msg_lspid);
    printf("Last Msg Received                               %d\n",ds.msg_lrpid);


return 0;
}
