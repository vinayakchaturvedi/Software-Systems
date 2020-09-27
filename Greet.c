#include<stdio.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Printing pre-added text from Greet\n");
    }
    else{
        for(int i = 1; i < argc; i++){
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
}