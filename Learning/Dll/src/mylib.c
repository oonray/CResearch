#include <stdio.h>
#include <ctype.h>
#include "headders/debug.h"

int a_message(const char *msg){
    printf("A String: %s\n",msg);
    return 0;
}

int uppercase(const char *msg){
    for(int i = 0; msg[i] != '\0'; i++){
        printf("%c", toupper(msg[i]));
    }
    printf("\n");
    return 0;
}

int lowercase(const char *msg){
    for(int i = 0; msg[i] != "\0"; i++){
        printf("%c",tolower(msg[i]));
    }
    printf("\n");
    return 0;
}

int fail_on_purpouse(const char *msg){
    return 1;
}

