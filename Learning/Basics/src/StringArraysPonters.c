#include <stdio.h>

int main(int argc, char *argv[]){
    char *StringArray[] = {"Hello"," ","World", "!", "\0"};

    for(char **i = StringArray; **i != '\0';i++){
        for(char *n = *i; *n != '\0'; n++){
            printf("%c\n",*n);
        }
    }
    printf("\n");
}