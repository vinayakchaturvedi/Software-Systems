#include<stdio.h>

int main(){

    printf("\n----------------------------Welcome to Hydra Bank :-)----------------------------------\n\n");
    int query;

    printf("Please login/signup to avail the services of the Bank\n\n");
    printf("Enter \"1\" for Existing user (Sign-in), \"2\" for New user (Sign-up): ");
    scanf("%d", &query);

    int retry = 1;

    while(1){
        if(query == 1){
            printf("Please Enter the login details: \n\n");
            break;
        }
        else if(query == 2){
            printf("Please Fill up the details: \n\n");
            break;
        }
        else{
            if(retry == 3){
                printf("Terminating the connection after 3 unsuccessful retries\n");
                return -1;
            }
            printf("Invalid selection Please Enter valid number: ");
            scanf("%d", &query);
            retry++;
        }
    }

    printf("\n---------------------------Thanks for Visiting Hydra Bank------------------------------\n\n");

}