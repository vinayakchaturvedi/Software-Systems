#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
extern int errno;
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;

}arg;
int main(int argc, char * argv[]){

	  //semaphore
          int key = ftok(".",'x');
          int sem;
  	  sem = semget(key,2,0);

	  arg.val=1;
	  semctl(sem,0,SETVAL,&arg);
	  semctl(sem,1,SETVAL,&arg);
	  printf("Before entering critical Section\n");
	  printf("Waiting for lock 1\n");
	  //locking
	  struct sembuf buf = {0,-1,0};
	  semop(sem,&buf,1);
	  printf("Inside Critical Section 1\n");
		
	  int shmid = shmget(key,1024,IPC_CREAT|0744);
	  char *data;
	  data = shmat(shmid,NULL,0);
	  printf("Enter data: ");
	  fgets(data,1024,stdin);

	  printf("Shared Memory 1  data: %s",data);
	  printf("\nPress Enter to enter Critical Section 2\n");
	  getchar();
	  //detach,unlock cs1 and lock cs2
	  shmdt(data);
	  buf.sem_op=1;
	  semop(sem,&buf,1);
	  int key2 = ftok(".",'w');
	  printf("Before entering critical Section\n");
	  printf("Waiting for lock2\n");
	  buf.sem_num=1;
	  buf.sem_op=-1;
	  semop(sem,&buf,1);
	  printf("Inside Critical Section 2\n");
	  shmid = shmget(key2,1024,IPC_CREAT|0744);
	  data =shmat(shmid,NULL,0);
	  printf("Enter data: ");
	  fgets(data,1024,stdin);

	  printf("Shared Memory 2 data: %s",data);
	  printf("Press enter to unlock");
	  shmdt(data);
	  buf.sem_op=1;
	  semop(sem,&buf,1);
	  getchar();
  return 0;
}
