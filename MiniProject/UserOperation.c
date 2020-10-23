#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include"AccountStruct.c"
#include"LoginStruct.c"

int Deposit(){

    printf("\nEnter you account number: ");
    long accountNumber;

}


int main(){

    printf("\n-------------------------------------Welcome User---------------------------------\n\n");
    printf("\nEnter the number corresponding to the operation that you want to perform:\n");
    printf("1: Deposit | 2: Withdraw | 3: Balance Enquiry | 4: Password Change | 5: View Details | 6: Exit");

    printf("Enter you choice: ");
    int operation;
    scanf("%d", &operation);

    switch (operation) {
        case 1: Deposit(); break;
        case 2: Withdraw(); break;
        case 3: BalanceEnquiry(); break;
        case 4: PasswordChange(); break;
        case 5: ViewDetail(); break;
        case 6: break;

        default: printf("Invalid Selection.\n");

    }

}