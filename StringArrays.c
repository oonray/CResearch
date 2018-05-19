#include <stdio.h>

int main(int argc, char *argv[]){
    char *StringArray[] = {"Hello", "World", "!"};
    for(int i = 0; i < sizeof(StringArray)/sizeof(char);i++){
        printf("%s", StringArray[i]);
    }

}