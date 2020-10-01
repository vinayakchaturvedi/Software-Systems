#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    int input;
    printf("Enter the child num (1, 2, 3) for whom you want: ");
    scanf("%d", &input);

    int childIds[3];                    //To capture the child ids of 3 children
    int childId = fork();               //Create 1st child
    if(childId){                        //if parent then go inside and store 1st & create 2nd child
        childIds[0] = childId;           //store 1st child's id
        childId = fork();               //call fork again and create 2nd child
        if(childId){                    //if parent then go inside and store 2nd create 3rd child
            childIds[1] = childId;       //store 2nd child's id
            childId = fork();           //call fork again and create 3rd child
            if(childId){                //if parent then go inside and store 3rd child
                childIds[2] = childId;

                printf("1st child id: %d\n2nd child id: %d\n3rd child id: %d\n", childIds[0], childIds[1], childIds[2]);
                //Now all the children are created and ids are stored in the array.
                int id = waitpid(childIds[input-1], NULL, 0);
                if(id != -1){
                    printf("Parent with process id: %d has successfully waited for child number: %d with process id: %d\n", getpid(), input, childIds[input-1]);
                }
                else{
                    perror("Error");
                }
            }
            else {
                childIds[2] = getpid();
            }
        }
        else {
            childIds[1] = getpid();
        }
    }
    else {
        childIds[0] = getpid();
    }



    //For proper testing let the input child sleep for 5 seconds and see whether parent is waiting or not.
    if(input == 1 && getpid() == childIds[0]){
        sleep(5);
        printf("I (pid: %d) am exiting now.\n", getpid());
    }
    if(input == 2 && getpid() == childIds[1]){
        sleep(5);
        printf("I (pid: %d) am exiting now.\n", getpid());
    }
    if(input == 3 && getpid() == childIds[2]){
        sleep(5);
        printf("I (pid: %d) am exiting now.\n", getpid());
    }



    return 0;
}