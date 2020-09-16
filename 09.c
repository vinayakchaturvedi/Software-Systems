#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>


int main(){

    struct stat status;
    char fileName[] = "MainFileQues9.txt";
    creat(fileName, 0644);

    int output = stat(fileName, &status);

    if (output == -1) {
        perror("STAT ERROR");
        return -1;
    }

    printf("I-node number:              %ld\n", (long) status.st_ino);
    printf("Number of Hard links:       %ld\n", (long) status.st_nlink);
    printf("UID:                        %ld\n", (long) status.st_uid);
    printf("GID:                        %ld\n", (long) status.st_gid);
    printf("File size:                  %lld bytes\n", (long long) status.st_size);
    printf("Block size:                 %ld bytes\n",  (long) status.st_blksize);
    printf("Number of blocks:           %lld\n",       (long long) status.st_blocks);
    printf("Time of last access:        %s", ctime(&status.st_atime));
    printf("Time of last modification:  %s", ctime(&status.st_mtime));
    printf("Time of last change:        %s", ctime(&status.st_ctime));

    return 0;
}