#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include"LoginStruct.c"
#include<string.h>

int main(){

    printf("Initializing DB...\n\n");
    int fd = open("./db/admin_Login_DB", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int fdAccountNumber = open("./db/accountNumber_DB", O_CREAT|O_WRONLY|O_TRUNC, 0644);

    struct Login adminLogin;
    long accountNumber = 0;

    memcpy(adminLogin.type, "AD", 2);
    memcpy(adminLogin.userName, "Admin", 5);
    memcpy(adminLogin.password, "root", 4);

    write(fd, &adminLogin, sizeof(adminLogin));
    write(fdAccountNumber, &accountNumber, sizeof(accountNumber));

    close(fd);
    close(fdAccountNumber);

    printf("Checking the initialization of DB...\n");
    struct Login test;
    long accountNumberTest;
    fd = open("./db/admin_Login_DB", O_RDONLY);
    fdAccountNumber = open("./db/accountNumber_DB", O_RDONLY);

    read(fd, &test, sizeof(test));
    read(fdAccountNumber, &accountNumberTest, sizeof(accountNumberTest));

    printf("Type: %s\nUserName: %s\nPassword: %s\n", test.type, test.userName, test.password);
    printf("Account number: %ld\n", accountNumberTest);

    close(fd);
    close(fdAccountNumber);

    return 0;
}

