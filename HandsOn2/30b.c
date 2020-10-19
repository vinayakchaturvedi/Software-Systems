#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<error.h>
#include<stdio.h>
int main(){
    int shm;
    printf("Enter Id  of shared  memory\n");
    scanf("%d",&shm);

    char *data;
    data = shmat(shm,NULL,SHM_RDONLY);
    printf("Reading from shared memory segment: %s\n",data);
    printf("Try to Overwrite\n");
    getchar();
    fgets(data,1024,stdin);
    printf("Reading from shared memory segment after trying to overwrite in Read Only Mode: %s\n",data);

return 0;
}
