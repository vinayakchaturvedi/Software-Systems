#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/sem.h>
#include<sys/shm.h>
extern int errno;

int main(int argc, char * argv[]){

 //semaphore
      int key = ftok(".",'y');
      int sem;
  	  sem = semget(key,1,0);

	  printf("Before entering critical Section\n");
	  printf("Waiting for lock\n");
	  //locking
	  struct sembuf buf = {0,-1,0};
	  semop(sem,&buf,1);
	  printf("Inside Critical Section\n");
		
	  int shmid = shmget(key,1024,IPC_CREAT|0744);
	  char *data;
	  data = shmat(shmid,NULL,0);
	  printf("Enter data\n");
	  fgets(data,1024,stdin);

	  printf("Shared Memory data: %s",data);
	  printf("Press Enter to unlock");
	  getchar();
	  //unlock the semaphore
	  buf.sem_op=1;
	  semop(sem,&buf,1);
  return 0;
}
