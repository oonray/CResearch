#include <stdio.h>
#include "headders/debug.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLACK, BLUE, GREEN, BROWN, ORHER
} EyeColor;

const char *Eye_Color_Names {
    "Black","Blue","Green","Brown","Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[]){
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;
    

    printf("What is your first name?");
    in = fgets(you.first_name,MAX_DATA-1, stdin);
    check(in, NULL, "Failed To Read The Name!");

    printf("What is your last name?");
    in = fgets(you.last_name,MAX_DATA-1, stdin);
    check(in, NULL, "Failed To Read The Name!");

    printf("How old are you?");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number!");

}

