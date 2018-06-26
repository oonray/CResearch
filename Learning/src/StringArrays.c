#include <stdio.h>

int main(int argc, char *argv[]){
    char *StringArray[] = {"Hello"," ","World", "!", "\0"};
    
    for(int i=0; StringArray[i][0] != '\0';i++){
        printf("%s",StringArray[i]);
    }

    printf("\n");
}