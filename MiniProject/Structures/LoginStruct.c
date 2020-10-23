#include<stdio.h>
#include<stdbool.h>

struct Login {

    char type[3];                   //AD : Admin, JA: Joint Account, NU: Normal User
    char userName[40];
    char password[40];
    bool active;
};