#include<stdio.h>
#include<unistd.h>

int main(){

    int currNiceValue = nice(0);
    printf("Priority of current process is: %d\n", currNiceValue);

    //change nice value -- Increase by 10
    printf("Increasing priority by 10\n");
    nice(10);

    currNiceValue = nice(0);
    printf("Nice value after modification is: %d\n", currNiceValue);

    return 0;
}