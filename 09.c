#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>


int main(){

    char p1[] = "Enter the name of the file: ";
    char temp[100];

    //-------------------------------Get Name of file1--------------------------
    write(2, p1, sizeof(p1));
    int bytesRead = read(1, temp, sizeof(temp));
    char fileName[bytesRead];
    for(int j = 0; j < bytesRead - 1; j++){
        fileName[j] = temp[j];
    }
    fileName[bytesRead-1] = '\0';

    //-------------------------------Retrieve the status--------------------------
    struct stat status;
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