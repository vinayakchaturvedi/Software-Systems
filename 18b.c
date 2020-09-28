#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "18_record_struct.c"

int main(){

    //------------------------------------------------------Variable Declaration------------------------------------------------------
    int fd = open("18_db", O_RDONLY);
    struct Record record;
    int recordNum;
    printf("Enter the record number (1, 2, 3) that you want to read lock: ");
    scanf("%d", &recordNum);
    getchar();

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((recordNum) * sizeof(record));
    lock.l_len = sizeof(record);
    lock.l_pid = getpid();

    //------------------------------------------------------Check lock------------------------------------------------------
    printf("Before entering critical section.\n");
    fcntl(fd, F_SETLKW, &lock);

    //------------------------------------------------------Inside Critical section--------------------------------------------------
    printf("Inside Critical section...\n");

    lseek(fd, ((recordNum-1) * sizeof(record)), SEEK_SET);
    read(fd, &record, sizeof(record));
    printf("Record Number: %d and Record Access count: %d\n", record.recordNumber, record.accessCount);

    printf("Press enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Record is Unlocked Now...\n");

    //------------------------------------------------------Unlocked Now--------------------------------------------------
    close(fd);

    return 0;
}

