#include<stdio.h>
#include<time.h>

struct Transaction {

    long long int amount;
    char transactionType[10];           //Deposit, WithDraw
    char timeofTransaction[40];
};