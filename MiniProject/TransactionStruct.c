#include<stdio.h>
#include<time.h>

struct Transaction {

    //struct tm* timeinfo;
    long long int amount;
    char transactionType[10];           //Deposit, WithDraw
};