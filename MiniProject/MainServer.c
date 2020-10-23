#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"AccountStruct.c"
#include"LoginStruct.c"

#define ADMIN 1
#define NORMAL_USER 2
#define JOINT_ACCOUNT 3

void printString(char *string){
    printf(" Testing: %s | ", string);
}


int add(int clientSockDesc){
    struct Account account;
    struct Login login;

    read(clientSockDesc, &account, sizeof(account));
    read(clientSockDesc, &login, sizeof(login));

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

int deleteAccount(int clientSockDesc){

    long accountNumber;
    read(clientSockDesc, &accountNumber, sizeof(accountNumber));

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        write(clientSockDesc, &fd, sizeof(fd));
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }
    close(fd);              //close read only

    if(bytes == 0 || !account.active){
        int notPresent = -2;
        write(clientSockDesc, &notPresent, sizeof(notPresent));
        return -1;
    }

    int success = 1;
    write(clientSockDesc, &success, sizeof(success));         //Positive number for success;
    write(clientSockDesc, &account, sizeof(account));
    fd = open("./db/account_DB", O_RDWR);

    //Lock Account DB
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(account));
    lock.l_len = sizeof(account);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    lseek(fd, ((count) * sizeof(account)), SEEK_SET);
    read(fd, &account, sizeof(account));



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
    while(currBytes != 0 && strncmp(account.Name, oldLogin.userName, strlen(account.Name)) != 0){
        currBytes = read(fd, &oldLogin, sizeof(oldLogin));
        count++;
    }

    //Lock Login DB
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(oldLogin));
    lock.l_len = sizeof(oldLogin);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);

    oldLogin.active = false;
    lseek(fd, ((count) * sizeof(oldLogin)), SEEK_SET);
    write(fd, &oldLogin, sizeof(oldLogin));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    write(clientSockDesc, &success, sizeof(success));
    close(fd);
    return 0;
}

int modify(int clientSockDesc){

    long accountNumber;
    read(clientSockDesc, &accountNumber, sizeof(accountNumber));

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        write(clientSockDesc, &fd, sizeof(fd));
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }
    close(fd);              //close read only

    if(bytes == 0){
        int notPresent = -2;
        write(clientSockDesc, &notPresent, sizeof(notPresent));
        return -1;
    }
    if(!account.active){
        int inActive = -3;
        write(clientSockDesc, &inActive, sizeof(inActive));
        return -1;
    }
    close(fd);

    int success = 1;
    write(clientSockDesc, &success, sizeof(success));   //Send success status      //Positive number for success;

    write(clientSockDesc, &account, sizeof(account));   //Send Old Values
    char oldName[40];
    strcpy(oldName, account.Name);

    read(clientSockDesc, &account, sizeof(account));    //Get new values

    fd = open("./db/account_DB", O_RDWR);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((count) * sizeof(account));
    lock.l_len = sizeof(account);
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
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

    write(clientSockDesc, &account, sizeof(account));   //Send Old Values

    return 0;
}

int search(int clientSockDesc){

    long accountNumber;
    read(clientSockDesc, &accountNumber, sizeof(accountNumber));

    struct Account account;
    long count = 0;                 //To keep track of account in file

    int fd = open("./db/account_DB", O_RDONLY);
    if(fd == -1){
        write(clientSockDesc, &fd, sizeof(fd));
        return -1;
    }

    int bytes = read(fd, &account, sizeof(account));
    while(bytes != 0 && account.accountNumber != accountNumber){
        bytes = read(fd, &account, sizeof(account));
        count++;
    }
    close(fd);              //close read only

    if(bytes == 0){
        int notPresent = -2;
        write(clientSockDesc, &notPresent, sizeof(notPresent));
        return -1;
    }
    if(!account.active){
        int inActive = -3;
        write(clientSockDesc, &inActive, sizeof(inActive));
        return -1;
    }

    int success = 1;
    write(clientSockDesc, &success, sizeof(success));         //Positive number for success;
    write(clientSockDesc, &account, sizeof(account));

    return 0;
}


int handleAdminRequest(int clientSockDesc){
    char welcome[] = "\n-----------------------------Welcome Admin-------------------------\n\nEnter the number corresponding to the operation that you want to perform:\n1: Add | 2: Delete | 3: Modify | 4: Search";
    write(clientSockDesc, welcome, sizeof(welcome));

    int operation;

    read(clientSockDesc, &operation, sizeof(operation));
    switch (operation) {
        case 1: add(clientSockDesc); break;
        case 2: deleteAccount(clientSockDesc); break;
        case 3: modify(clientSockDesc); break;
        case 4: search(clientSockDesc); break;
    }
    return 0;
}

int handleUserRequest(int clientSockDesc){

}

int validateCredentials(int clientSockDesc, int userType){

    char db[30];

    switch (userType) {
        case 1: memcpy(db, "./db/admin_Login_DB", strlen("./db/admin_Login_DB")); break;
        case 2: memcpy(db, "./db/user_login_DB", strlen("./db/user_login_DB")); break;
        case 3: memcpy(db, "./db/user_login_DB", strlen("./db/user_login_DB")); break;
    }

    char userName[40], password[40];

    write(clientSockDesc, "UserName: ", sizeof("UserName: "));
    read(clientSockDesc, &userName, sizeof(userName));

    write(clientSockDesc, "Password: ", sizeof("Password: "));
    read(clientSockDesc, &password, sizeof(password));

    int fd = open(db, O_RDONLY);
    struct Login record;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    fcntl(fd, F_SETLKW, &lock);
    int currBytes = read(fd, &record, sizeof(record));
    while(currBytes != 0){

        if(strncmp(record.userName, userName, strlen(record.userName)) == 0 && strncmp(record.password, password, strlen(record.password)) == 0){
            write(clientSockDesc, "Logged-in successfully", sizeof("Logged-in successfully"));

            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);

            //go to services
            if(userType == ADMIN) handleAdminRequest(clientSockDesc);
            //else handleUserRequest();

            close(fd);
            return 0;
        }
        currBytes = read(fd, &record, sizeof(record));
    }
    if(currBytes == 0){
        write(clientSockDesc, "-1", sizeof("-1"));
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
    }
    close(fd);
    return 0;
}


int handleClientRequest(int clientSockDesc, int clientNum){

    int userType;

    char temp[] = "Server has accepted the request.\nEnter \"1\" for Administrator login \"2\" for Normal User login \"3\" for Joint Account holder login: ";
    write(clientSockDesc, temp, sizeof(temp) - 1);

    //--------------------------Get the user type whether user is admin, normal user, joint account holder----------------
    read(clientSockDesc, &userType, sizeof(userType));
    validateCredentials(clientSockDesc, userType);


    return 0;        //Terminate the child process
}

int main(){
    struct sockaddr_in server, client;
    int sockDesc, clientSockDesc, clientLen;

    sockDesc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5555);

    bind(sockDesc, (struct sockaddr *)&server, sizeof(server));
    listen(sockDesc, 4);    //At max 4 clients can wait in the waiting queue at any time.

    char temp[] = "Waiting for the client...\n";
    int clientNum = 1;
    while(1){                       //Keep running and accept the incoming requests...
        printf("%s", temp);
        clientLen = sizeof(client);
        clientSockDesc = accept(sockDesc, (struct sockaddr *)&client, &clientLen);
        printf("Connected to a client number: %d\n", clientNum);

        if(!fork()){        //child to serve client's request
            close(sockDesc);        //close socket descriptor of parent because it is not required in serving the request by child.
            handleClientRequest(clientSockDesc, clientNum);
            return 0;
        }
        else{           //Parent -- continue accepting the request of other clients.
            clientNum++;
            close(clientSockDesc);   //Close client Socket Descriptor in parent because it is not required by parent.
        }
    }
    close(sockDesc);
    return 0;
}