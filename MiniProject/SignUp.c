#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include"AccountStruct.c"
#include"LoginStruct.c"

int main(){

    struct Account account;
    struct Login login;

    printf("Enter the following Details: \n");
    printf("Enter 1 for Normal Account and 2 for Joint Account: ");
    int type;
    scanf("%d", &type);
    if(type == 1) memcpy(account.type, "NU", 2);
    else if(type == 2) memcpy(account.type, "JA", 2);
    else{
        printf("Invalid Selection.\n");
        return -1;
    }
    memcpy(login.type, &account.type, 2);

    printf("Name (This will also be your account login userName): ");
    scanf(" %[^\n]", account.Name);
    memcpy(login.userName, &account.Name, sizeof(account.Name));

    if(type == 2){
        printf("Secondary Account Holder Name: ");
        scanf(" %[^\n]", account.SecondaryAccountHolderName);
    }

    printf("Password: ");
    scanf(" %[^\n]", login.password);

    printf("Contact Number: ");
    scanf(" %ld", &account.contactNo);

    printf("Enter the amount by which you want to open your account: ");
    scanf(" %lld", &account.availableAmount);

    account.transactionsCount = 1;

    struct Transaction transaction;
    transaction.amount = account.availableAmount;
    memcpy(transaction.transactionType, "Deposit", 7);

    account.transactions[account.transactionsCount - 1] = transaction;

    int userLoginFd = open("./db/user_login_DB", O_CREAT|O_RDWR, 0644);
    int accountFd = open("./db/account_DB", O_CREAT|O_RDWR, 0644);
    int accountNumberFd = open("./db/accountNumber_DB", O_RDWR);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    //Lock accountNumber_DB
    fcntl(accountNumberFd, F_SETLKW, &lock);
    lseek(accountNumberFd, 0, SEEK_SET);

    long accountNumber;
    read(accountNumberFd, &accountNumber, sizeof(accountNumber));
    account.accountNumber = ++accountNumber;
    lseek(accountNumberFd, 0, SEEK_SET);
    write(accountNumberFd, &accountNumber, sizeof(accountNumber));
    lock.l_type = F_UNLCK;
    fcntl(accountNumberFd, F_SETLK, &lock);

    //Lock user_login_DB
    lock.l_whence = SEEK_END;
    lock.l_len = sizeof(login);
    fcntl(userLoginFd, F_SETLKW, &lock);

    lseek(userLoginFd, 0, SEEK_END);
    write(userLoginFd, &login, sizeof(login));
    lock.l_type = F_UNLCK;
    fcntl(userLoginFd, F_SETLK, &lock);

    //Lock account_DB
    lock.l_type = F_WRLCK;
    lock.l_len = sizeof(account);
    fcntl(accountFd, F_SETLKW, &lock);

    lseek(accountFd, 0, SEEK_END);
    write(accountFd, &account, sizeof(account));
    lock.l_type = F_UNLCK;
    fcntl(accountFd, F_SETLK, &lock);

}