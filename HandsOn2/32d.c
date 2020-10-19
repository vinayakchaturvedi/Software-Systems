#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/sem.h>
#include<sys/shm.h>
extern int errno;

int main(int argc, char * argv[]){

	  // remove semaphore
	  printf("Enter sem id to remove: ");
	  int sem;
	  scanf("%d",&sem);

	  semctl(sem,0,IPC_RMID,NULL);
  	  return 0;	
}
