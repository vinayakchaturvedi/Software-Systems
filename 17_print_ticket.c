#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "17_ticket_struct.c"

int main(){

    struct Ticket ticket;
    int fd = open("17_db", O_RDONLY);
    read(fd, &ticket, sizeof(ticket));
    printf("Current Ticket number: %d\n", ticket.ticketNumber);
    close(fd);

    return 0;
}

