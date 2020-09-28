#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>


int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Please provide file name as a command line argument.\n");
        return -1;
    }

    //-------------------------------Retrieve the status--------------------------
    struct stat status;
    int output = lstat(argv[1], &status);

    if (output == -1) {
        perror("LSTAT ERROR");
        return -1;
    }

    printf("File type:                ");

    switch (status.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }


    return 0;
}