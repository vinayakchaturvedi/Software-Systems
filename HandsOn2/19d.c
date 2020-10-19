#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(){

mknod("19_fifo_using_mknod",S_IFIFO|0744,0);

}
