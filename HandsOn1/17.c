#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "17_ticket_struct.c"

int main(){

    //------------------------------------------------------Variable Declaration------------------------------------------------------
    int fd = open("17_db", O_RDWR);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    //------------------------------------------------------Check lock------------------------------------------------------
    printf("Before entering critical section.\n");
    fcntl(fd, F_SETLKW, &lock);

    //------------------------------------------------------Inside Critical section--------------------------------------------------
    printf("Inside Critical section...\n");
    struct Ticket ticket;
    read(fd, &ticket, sizeof(ticket));
    printf("Old Ticket number: %d\n", ticket.ticketNumber);

    ticket.ticketNumber = ticket.ticketNumber + 1;
    lseek(fd, 0, SEEK_SET);

    printf("Ticket number has been updated and new number is: %d\n", ticket.ticketNumber);
    write(fd, &ticket, sizeof(ticket));

    printf("Press enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("DB is Unlocked Now...\n");

    //------------------------------------------------------Unlocked Now--------------------------------------------------
    close(fd);

    return 0;
}

