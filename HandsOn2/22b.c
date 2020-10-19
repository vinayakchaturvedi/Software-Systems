#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
extern int errno;

int main(int argc, char * argv[]){
  int fd = open("myfifo",O_RDONLY);
  int timeout=10;                   //TimeOut For 10 seconds
  struct timeval tv;
  tv.tv_sec = timeout;
  tv.tv_usec=0;
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(fd,&readfds);
  int ret = select(fd+1,&readfds,NULL,NULL,&tv);


  if (ret==-1)
  {
	perror("Error occured in select\n");
	printf("%d\n",errno);

  }
  else if (ret==0){
	printf("No Data within %d seconds\n",timeout);

  }
  else{
		char buf[100];
		int len = sizeof(buf)-1;
		int read_ret;
		read_ret=read(fd,buf,len);
		if(read_ret==-1)
			perror("read");
		else
			write(STDOUT_FILENO,buf,strlen(buf));
  }
  return 0;	
}
