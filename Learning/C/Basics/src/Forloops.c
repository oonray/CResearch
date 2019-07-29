#include <stdio.h>

int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("Usage: %s <arg1> <arg2>", argv[0]);
        return 1; //Ending a program prematurly.
    }

    printf("Argument: %s\n",argv[1]);
    printf("Foorloop: ");

    for(int i=0; argv[1][i] != '\0';i++){
        char letter = argv[1][i];
        printf("%c",letter);
    }
    printf("\n");

    return 1;
}