#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include"./Structures/AccountStruct.c"
#include"./Structures/LoginStruct.c"

#define ADMIN 1
#define NORMAL_USER 2
#define JOINT_ACCOUNT 3

void printAccountDetails(struct Account account){

    printf("\nAccountNumber:                      %ld\n", account.accountNumber);
    printf("Type:                               %s\n\n", strncmp(account.type, "JA", strlen("JA")) != 0 ? "Normal Account":"Joint Account");
    printf("Name:                               %s\n", account.Name);
    printf("UserName1 (For Login Purpose):      %s\n\n", account.userName);

    if(strncmp(account.type, "JA", strlen("JA")) == 0){
    printf("Secondary AccountHolder Name:       %s\n\n",
            account.SecondaryAccountHolderName);
    }


    printf("Contact Number:                     %ld\nAvailable Amount:                   %lld\n\n",
            account.contactNo, account.availableAmount);

}

//----------------------Admin Operations---------------------
int add(int sockDesc){
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

    printf("Name: ");
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
    login.active = true;

    struct Transaction transaction;
    transaction.amount = account.availableAmount;
    memcpy(transaction.transactionType, "Deposit", 7);

    account.transactions[account.transactionsCount - 1] = transaction;

    write(sockDesc, &account, sizeof(account));
    write(sockDesc, &login, sizeof(login));

    sleep(1);

    read(sockDesc, &account, sizeof(account));

    system("clear");
    printf("\nSuccessfully added the account PFB Details of the account: \n");
    printAccountDetails(account);
}

int deleteAccount(int sockDesc){

    long accountNumber;
    struct Account account;
    char buff[1000];

    printf("\nEnter the account number that you want to Delete: ");
    scanf("%ld", &accountNumber);
    write(sockDesc, &accountNumber, sizeof(accountNumber));

    int status;
    read(sockDesc, &status, sizeof(status));
    if(status == -1){
        printf("No accounts are present.\n");
        return -1;
    }
    else if(status == -2){
        printf("Entered account number not present.\n");
        return -1;
    }
    else if(status == -3){
        printf("Entered account number is in-active.\n");
        return -1;
    }

    read(sockDesc, &account, sizeof(account));

    printf("\nCurrent Details of the selected account: \n");
    printAccountDetails(account);

    int success;
    read(sockDesc, &success, sizeof(success));
    if(success != 1) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("Successfully removed the account: %ld\n", accountNumber);

    return 0;

}

int modify(int sockDesc){

    long accountNumber;
    struct Account account;

    printf("\nEnter the account number that you want to modify: ");
    scanf("%ld", &accountNumber);
    write(sockDesc, &accountNumber, sizeof(accountNumber));

    int status;
    read(sockDesc, &status, sizeof(status));
    if(status == -1){
        printf("No accounts are present.\n");
        return -1;
    }
    else if(status == -2){
        printf("Entered account number not present.\n");
        return -1;
    }
    else if(status == -3){
        printf("Entered account number is in-active.\n");
        return -1;
    }

    read(sockDesc, &account, sizeof(account));

    printf("\nCurrent Details of the selected account: \n");
    printAccountDetails(account);

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

    write(sockDesc, &account, sizeof(account));;
    read(sockDesc, &account, sizeof(account));;

    system("clear");
    printf("\nUpdated Details of the selected account: \n");
    printAccountDetails(account);

    return 0;
}

int search(int sockDesc){

    long accountNumber;
    struct Account account;
    char buff[1000];

    printf("\nEnter the account number that you want to Search: ");
    scanf("%ld", &accountNumber);
    write(sockDesc, &accountNumber, sizeof(accountNumber));

    int status;
    read(sockDesc, &status, sizeof(status));
    if(status == -1){
        printf("No accounts are present.\n");
        return -1;
    }
    else if(status == -2){
        printf("Entered account number not present.\n");
        return -1;
    }
    else if(status == -3){
        printf("Entered account number is in-active.\n");
        return -1;
    }

    read(sockDesc, &account, sizeof(account));

    system("clear");
    printf("\nDetails of the selected account: \n");
    printAccountDetails(account);

    return 0;

}

int adminSpecificTask(int sockDesc){
    char welcome[] = "\n-----------------------------Welcome Admin-------------------------\n\n";
    printf("%s", welcome);
    while(true){
        printf("\nEnter the number corresponding to the operation that you want to perform:\n1: Add | 2: Delete | 3: Modify | 4: Search | 5: Exit\n");
        int operation;               //--Operations for admin
        scanf("%d", &operation);

        if(operation < 1 || operation > 5){
            printf("Invalid Selection\n");
            return -1;
        }

        write(sockDesc, &operation, sizeof(operation));
        if(operation == 5) break;

        switch (operation) {
            case 1: add(sockDesc); break;
            case 2: deleteAccount(sockDesc); break;
            case 3: modify(sockDesc); break;
            case 4: search(sockDesc); break;
        }
        printf("\n*********************************************************************\n");
    }
    return 0;
}
//----------------------Admin Operations Done---------------------

//----------------------User Operations----------------------
void printTransaction(struct Account account){
    printf("Last 5 Transaction Details: \n");
    int last = account.transactionsCount - 1;
    int start = (0 > account.transactionsCount - 5) ? 0 : account.transactionsCount - 5;
    printf("    Type    |      Amount        |       Date & Time \n");
    for(int i = start; i <= last; i++){
        struct Transaction currTransaction = account.transactions[i];
        printf("   %s        %lld          %s\n", currTransaction.transactionType,
                currTransaction.amount, currTransaction.timeofTransaction);
    }
}

int deposit(int sockDesc){
    int status;
    char buff[1000];
    read(sockDesc, &status, sizeof(status));

    if(status == -1){
        printf("Something went wrong...\n");
        return -1;
    }
    long long int depositAmount;
    printf("Enter the amount: ");
    scanf("%lld", &depositAmount);
    write(sockDesc, &depositAmount, sizeof(depositAmount));

    printf("Processing...\n\n");
    sleep(1);
    read(sockDesc, buff, sizeof(buff));
    printf("%s\n", buff);
    return 0;
}

int withdraw(int sockDesc){
    int status;
    char buff[1000];
    read(sockDesc, &status, sizeof(status));

    if(status == -1){
        printf("Something went wrong...\n");
        return -1;
    }
    long long int withdrawAmount;
    printf("Enter the amount: ");
    scanf("%lld", &withdrawAmount);
    write(sockDesc, &withdrawAmount, sizeof(withdrawAmount));

    read(sockDesc, &status, sizeof(status));
    if(status == -1){
        printf("Insufficient Balance\n");
        return -1;
    }
    printf("Processing...\n\n");
    sleep(1);
    read(sockDesc, buff, sizeof(buff));
    printf("%s\n", buff);
    return 0;

}

int balanceEnquiry(int sockDesc){
    int status;
    char buff[1000];
    read(sockDesc, &status, sizeof(status));

    if(status == -1){
        printf("Something went wrong...\n");
        return -1;
    }

    printf("Processing...\n\n");
    sleep(1);
    read(sockDesc, buff, sizeof(buff));
    printf("%s\n", buff);
    return 0;

}

int passwordChange(int sockDesc){
    printf("Enter new password: ");
    char buff[40];
    scanf(" %[^\n]", buff);
    write(sockDesc, buff, sizeof(buff));

    int status;
    read(sockDesc, &status, sizeof(status));
    if(status == -1){
        printf("Something went wrong.\n");
        return -1;
    }

    printf("Successfully changed the password.\n");
    return 0;
}

int viewDetails(int sockDesc){
    int status;
    struct Account account;
    read(sockDesc, &status, sizeof(status));

    if(status == -1){
        printf("Something went wrong...\n");
        return -1;
    }

    printf("Processing...\n\n");
    sleep(1);

    read(sockDesc, &account, sizeof(account));

    system("clear");
    printf("\nDetails of the your account: \n");
    printAccountDetails(account);

    printTransaction(account);
    return 0;

}

int userSpecificTask(int sockDesc){
    char welcome[] = "\n-----------------------------Welcome User-------------------------\n\n";
    printf("%s", welcome);
    while(true){
        printf("\nEnter the number corresponding to the operation that you want to perform:\n1: Deposit | 2: Withdraw | 3: Balance Enquiry | 4: Password Change | 5: View Details | 6: Exit\n");
        int operation;              //--Operations for user
        scanf("%d", &operation);

        if(operation < 1 || operation > 7){
                printf("Invalid Selection\n");
                return -1;
            }
            write(sockDesc, &operation, sizeof(operation));
            if(operation == 6) break;
            switch (operation) {
                case 1: deposit(sockDesc); break;
                case 2: withdraw(sockDesc); break;
                case 3: balanceEnquiry(sockDesc); break;
                case 4: passwordChange(sockDesc); break;
                case 5: viewDetails(sockDesc); break;
            }
            printf("\n*********************************************************************\n");
    }
        return 0;
}

//----------------------User Operations Done----------------------
int main(){
    struct sockaddr_in server;
    int sockDesc, messageLen;
    char buff[1000];
    char result;

    sockDesc = socket(AF_INET, SOCK_STREAM, 0);     //Establishing the connection b/w client and server.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //Loop back address because both are on same machine.
                                // can give INADDR_ANY as well for same machine and if server is on diff machine
                                //provide its IP address in this field.
    server.sin_port = htons(5555);
    printf("Waiting to connect to the server...\n");
    int connectionStatus = connect(sockDesc, (struct sockaddr *)&server, sizeof(server));      //Sending the connect request to server.

    int retryCount = 0;
    while(connectionStatus == -1 && retryCount < 3){
        printf("Connection failed with server... Retrying in 3 seconds.\n");
        retryCount++;
        sleep(3);
        connectionStatus = connect(sockDesc, (struct sockaddr *)&server, sizeof(server));      //Again Sending the connect request to server.
    }
    if(connectionStatus == -1){
        printf("Could not establish the connection with server even after %d retries hence terminating the request now.\n", retryCount);
        return -1;
    }

    read(sockDesc, buff, sizeof(buff));
    printf("%s", buff);


    //-----------------------------------------------Send whether you are admin, normal user, joint account holder----------------
    int userType;
    scanf("%d", &userType);
    if(userType != 1 && userType != 2 && userType != 3){
        printf("Invalid selection\n");
        return -1;
    }

    write(sockDesc, &userType, sizeof(userType));


    //---------------------User Name----------------------
    char userName[40], password[40];

    read(sockDesc, buff, sizeof(buff));
    printf("%s", buff);
    scanf(" %[^\n]", userName);
    write(sockDesc, &userName, sizeof(userName));

    //---------------------Password----------------------
    read(sockDesc, buff, sizeof(buff));
    printf("%s", buff);
    scanf(" %[^\n]", password);
    write(sockDesc, &password, sizeof(password));

    //-------------------------User Name password validation result-------------------------
    read(sockDesc, buff, sizeof(buff));
    if(strncmp("-1", buff, strlen(buff)) == 0){
        printf("Incorrect UserName/Password\n");
        close(sockDesc);
        return -1;
    }
    printf("%s\n", buff);

    //----------------Admin Specific---------
    if(userType == 1) return adminSpecificTask(sockDesc);

    //----------------User Specific---------
    else return userSpecificTask(sockDesc);

    close(sockDesc);
    return 0;
}

