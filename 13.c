#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

int main(){

   fd_set readfds;
   struct timeval timeout;
   int retval;

   //----------------------------check stdin (fd 0) to see when it has input----------------------------
   FD_ZERO(&readfds);
   FD_SET(0, &readfds);

   //------------------------------------Wait up to 10 seconds-----------------------------------------
   timeout.tv_sec = 10;
   timeout.tv_usec = 0;

   retval = select(1, &readfds, NULL, NULL, &timeout);

   if (retval == -1)
       perror("select()");
   else if (retval)
       printf("Data is available now.\n");
   else
       printf("No data within 10 seconds.\n");

   return 0;
}