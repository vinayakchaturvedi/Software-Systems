#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/sem.h>
extern int errno;

int main(int argc, char * argv[]){

  int fd = open("record",O_RDWR);


  if (fd==-1)
  {
	perror("Error occured in open\n");
	printf("%d\n",errno);

  }
  else{
	  struct database{
	  int ticket_count;
	  } ;

	  struct database db;

	  //semaphore
	  int key = ftok(".",'z');
	  int sem;
	  sem = semget(key,1,IPC_CREAT|0766);
	  if(sem==-1){
	   perror("semget");
	   return 0;
	  
	  }	
	  struct sembuf buf = {0,-1,0};
	  printf("Before entering critical Section\n");
	  printf("Waiting for lock\n");
	  semop(sem,&buf,1);
	  printf("Inside Critical Section\n");

	  read(fd,&db,sizeof(db));
	  printf("Current ticket number %d\n",db.ticket_count);
	  db.ticket_count++;
	  lseek(fd,0,SEEK_SET);
	  write(fd,&db,sizeof(db));
	  printf("New ticket number is %d\n", db.ticket_count);
	  printf("Press Enter to unlock");
	  getchar();
	  //unlock the semaphore
	  buf.sem_op=1;
	  semop(sem,&buf,1);
  }
  return 0;	
}
