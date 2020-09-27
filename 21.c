#include<stdio.h>
#include<unistd.h>

int main(){

    int childId = fork();
    if(childId){
        printf("Parent process id: %d\n", getpid());
        printf("Child process id: %d\n", childId);
    }

    return 0;
}