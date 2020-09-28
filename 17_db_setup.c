#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "17_ticket_struct.c"

int main(){

    int fd = open("17_db", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    struct Ticket ticket;
    ticket.ticketNumber = 0;
    write(fd, &ticket, sizeof(ticket));
    close(fd);

    printf("Checking the initialization of DB...\n");
    struct Ticket test;
    fd = open("17_db", O_RDONLY);
    read(fd, &test, sizeof(test));
    printf("Ticket number: %d\n", test.ticketNumber);
    close(fd);

    return 0;
}

