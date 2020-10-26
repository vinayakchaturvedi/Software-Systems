#include<stdio.h>
#include<stdbool.h>
#include"TransactionStruct.c"

struct Account {

    long accountNumber;
    char type[3];                   //JA: Joint Account, NU: Normal User
    char Name[40];
    char SecondaryAccountHolderName[40];        //Will be filled only for Joint accounts;
    char userName[40];
    char userName2[40];

    bool active;

    long contactNo;
    long long int availableAmount;

    int transactionsCount;
    struct Transaction transactions[200];

};