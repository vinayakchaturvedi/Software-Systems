#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdbool.h>
#include"./Structures/AccountStruct.c"
#include"./Structures/LoginStruct.c"

int main(){

    int accountFd = open("./db/account_DB", O_CREAT|O_RDWR, 0644);

    struct Account account;
    struct flock lock;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    //Lock account_DB
    fcntl(accountFd, F_SETLKW, &lock);

    //Reading all account details
    int bytes = read(accountFd, &account, sizeof(account));
    while(bytes != 0){
            printf("AccountNumber: %ld\nName: %s\nSecondary AccountHolder Name (If Joint Account): %s\nUserName (For Login Purpose): %s\nType: %s\nActive: %s\nContact Number: %ld\nAvailable Amount: %lld\n\n",
                account.accountNumber,
                account.Name, account.SecondaryAccountHolderName,account.userName,
                account.type, account.active ? "true":"false", account.contactNo, account.availableAmount);

        bytes = read(accountFd, &account, sizeof(account));
    }

    lock.l_type = F_UNLCK;
    fcntl(accountFd, F_SETLK, &lock);
    close(accountFd);
}