#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(){

mkfifo("19_fifo_using_mkfifo",0744);

}
