#include<stdio.h>
#include<stdbool.h>
#include"TransactionStruct.c"

struct Account {

    long accountNumber;
    char type[3];                   //JA: Joint Account, NU: Normal User
    char Name[40];
    char SecondaryAccountHolderName[40];        //Will be filled only for Joint accounts;

    bool active;

    long contactNo;
    long long int availableAmount;

    struct Transaction transactions[1000];
    int transactionsCount;

};