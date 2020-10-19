#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/sem.h>
extern int errno;

int main(int argc, char * argv[]){

	  //semaphore
	  int key = ftok(".",'z');
	  int sem;
	  sem = semget(key,1,IPC_CREAT|0744);
	  if(sem==-1){
	  perror("semget");
	  return 0;
	  }	  
	  struct sembuf buf = {0,1,0}; 
	  semop(sem,&buf,1);
  	  return 0;	
}
