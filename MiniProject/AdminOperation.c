#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<fcntl.h>
#include"AccountStruct.c"
#include"LoginStruct.c"

int add(){
    struct Account account;
    struct Login login;

    printf("\nEnter the following Details: \n");
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
    account.active = true;

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

    close(accountNumberFd);

    //Lock user_login_DB
    lock.l_whence = SEEK_END;
    lock.l_len = sizeof(login);
    fcntl(userLoginFd, F_SETLKW, &lock);

    lseek(userLoginFd, 0, SEEK_END);
    write(userLoginFd, &login, sizeof(login));
    lock.l_type = F_UNLCK;
    fcntl(userLoginFd, F_SETLK, &lock);

    close(userLoginFd);

    //Lock account_DB
    lock.l_type = F_WRLCK;
    lock.l_len = sizeof(account);
    fcntl(accountFd, F_SETLKW, &lock);

    lseek(accountFd, 0, SEEK_END);
    write(accountFd, &account, sizeof(account));
    lock.l_type = F_UNLCK;
    fcntl(accountFd, F_SETLK, &lock);

    close(accountFd);
}

int modify(){
    long accountNumber;
    printf("\nEnter the account number that you want to modify: ");
    scanf("%ld", &accountNumber);

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        printf("No accounts are present.\n");
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }

    if(bytes == 0){
        printf("Entered account number not present.\n");
        close(fd);
        return -1;
    }

    if(!account.active){
        printf("Entered account is not active.\n");
        close(fd);
        return -1;
    }

    close(fd);

    fd = open("./db/account_DB", O_RDWR);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(account));
    lock.l_len = sizeof(account);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    read(fd, &account, sizeof(account));

    char oldName[40];
    strcpy(oldName, account.Name);

    printf("\nCurrent Details of the selected account: \n");
    printf("AccountNumber: %ld\nName: %s\nSecondary AccountHolder Name (If Joint Account): %s\nType: %s\nContact Number: %ld\nAvailable Amount: %lld\n\n",
                account.accountNumber,
                account.Name, account.SecondaryAccountHolderName,
                account.type, account.contactNo, account.availableAmount);

    printf("Enter the modified value in the respected field or Enter -1 for no change\n");

    printf("Enter 1 for Normal Account and 2 for Joint Account: ");
    int type;
    scanf("%d", &type);
    if(type != -1){
        if(type == 1) memcpy(account.type, "NU", 2);
        else if(type == 2) memcpy(account.type, "JA", 2);
        else{
            printf("Invalid Selection.\n");
            return -1;
        }
    }

    printf("Name : ");
    char name[40];
    scanf(" %[^\n]", name);

    if((strncmp("-1", name, 2)) != 0){
        memcpy(account.Name, &name, sizeof(name));
    }

    if(type == 2){
        char sname[40];
        printf("Secondary Account Holder Name: ");
        scanf(" %[^\n]", sname);
        if((strncmp("-1", sname, 2)) != 0){
            memcpy(account.SecondaryAccountHolderName, &sname, sizeof(sname));
        }
    }

    long contactNo;
    printf("Contact Number: ");
    scanf(" %ld", &contactNo);
    if(contactNo != -1){
        account.contactNo = contactNo;
    }

    long long int availableAmount;
    printf("Available amount: ");
    scanf(" %lld", &availableAmount);
    if(availableAmount != -1){
        account.availableAmount = availableAmount;
    }

    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    write(fd, &account, sizeof(account));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    fd = open("./db/user_login_DB", O_RDWR);
    struct Login oldLogin;

    int currBytes = read(fd, &oldLogin, sizeof(oldLogin));
    count = 0;
    while(currBytes != 0 && strncmp(oldName, oldLogin.userName, strlen(oldName)) != 0){
        currBytes = read(fd, &oldLogin, sizeof(oldLogin));
        count++;
    }

    lseek(fd, ((count) * sizeof(oldLogin)), SEEK_SET);
    memcpy(oldLogin.type, &account.type, 2);
    memcpy(oldLogin.userName, &account.Name, sizeof(account.Name));

    lseek(fd, ((count) * sizeof(oldLogin)), SEEK_SET);
    write(fd, &oldLogin, sizeof(oldLogin));
    close(fd);

    printf("\nUpdated Details of the selected account: \n");
    printf("AccountNumber: %ld\nName: %s\nSecondary AccountHolder Name (If Joint Account): %s\nType: %s\nContact Number: %ld\nAvailable Amount: %lld\n\n",
                account.accountNumber,
                account.Name, account.SecondaryAccountHolderName,
                account.type, account.contactNo, account.availableAmount);


    return 0;
}

int deleteAccount(){

    long accountNumber;
    printf("\nEnter the account number that you want to Delete: ");
    scanf("%ld", &accountNumber);

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        printf("No accounts are present.\n");
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }

    if(bytes == 0){
        printf("Entered account number not present.\n");
        close(fd);
        return -1;
    }

    close(fd);

    fd = open("./db/account_DB", O_RDWR);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(account));
    lock.l_len = sizeof(account);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    read(fd, &account, sizeof(account));

    char oldName[40];
    strcpy(oldName, account.Name);

    printf("\nCurrent Details of the selected account: \n");
    printf("AccountNumber: %ld\nName: %s\nSecondary AccountHolder Name (If Joint Account): %s\nType: %s\nContact Number: %ld\nAvailable Amount: %lld\n\n",
                account.accountNumber,
                account.Name, account.SecondaryAccountHolderName,
                account.type, account.contactNo, account.availableAmount);

    account.active = false;
    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    write(fd, &account, sizeof(account));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);

    fd = open("./db/user_login_DB", O_RDWR);
    struct Login oldLogin;

    int currBytes = read(fd, &oldLogin, sizeof(oldLogin));
    count = 0;
    while(currBytes != 0 && strncmp(oldName, oldLogin.userName, strlen(oldName)) != 0){
        currBytes = read(fd, &oldLogin, sizeof(oldLogin));
        count++;
    }

    lseek(fd, ((count) * sizeof(oldLogin)), SEEK_SET);
    //free(oldLogin);

    close(fd);
    return 0;

}

int search(){
    long accountNumber;
    printf("\nEnter the account number that you want to Search: ");
    scanf("%ld", &accountNumber);

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        printf("No accounts are present.\n");
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }

    if(bytes == 0){
        printf("Entered account number not present.\n");
        close(fd);
        return -1;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(account));
    lock.l_len = sizeof(account);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    read(fd, &account, sizeof(account));

    char oldName[40];
    strcpy(oldName, account.Name);

    printf("\nCurrent Details of the selected account: \n");
    printf("AccountNumber: %ld\nName: %s\nSecondary AccountHolder Name (If Joint Account): %s\nType: %s\nContact Number: %ld\nAvailable Amount: %lld\n\n",
                account.accountNumber,
                account.Name, account.SecondaryAccountHolderName,
                account.type, account.contactNo, account.availableAmount);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
}

int main(){

    printf("\n-----------------------------Welcome Admin-------------------------\n");
    printf("\nEnter the number corresponding to the operation that you want to perform:\n");
    printf("1: Add | 2: Delete | 3: Modify | 4: Search\n");
    printf("Enter you choice: ");
    int operation;
    scanf("%d", &operation);

    switch (operation) {
        case 1: add(); break;
        case 2: deleteAccount(); break;
        case 3: modify(); break;
        case 4: search(); break;

        default: printf("Invalid Selection.\n");

    }
    return 0;
}