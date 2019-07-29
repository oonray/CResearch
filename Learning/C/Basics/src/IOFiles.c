#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "headders/debug.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLACK, BLUE, GREEN, BROWN, OTHER_EYES
} EyeColor;

const char *Eye_Color_Names[] = { "Black","Blue","Green","Brown","Other" };

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[]){
    Person you = {.age = 0};
    char *in = NULL;
    

    printf("What is your first name?");
    in = fgets(you.first_name,MAX_DATA-1, stdin);
    check(in != NULL, "Failed To Read The Name!");

    printf("What is your last name?");
    in = fgets(you.last_name,MAX_DATA-1, stdin);
    check(in != NULL, "Failed To Read The Name!");

    printf("How old are you?");
    char integer[MAX_DATA];
    fgets(integer, MAX_DATA-1, stdin);
    you.age = atoi(integer);

    check(you.age > 0, "You have to enter a number!");


    printf("What color are your eyes?\n");
    for(int i = 0;i<= OTHER_EYES; i++){
        printf("%d, %s\n", i+1, Eye_Color_Names[i]);
    }
    printf(">");

    int eyes = -1;
    char integer2[MAX_DATA];
    fgets(integer2, MAX_DATA-1, stdin);
    eyes = atoi(integer2);

    check(eyes > 0, "You have entered an invalid number!");

    you.eyes = eyes-1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "That is not an option!");

    printf("How much do you make an hour?");
    fscanf(stdin,"%f",&you.income);
    check(you.income > 0, "Enter a floating point number!");

    printf("----------RESULTS---------------\n");

    printf("First Name: %s\n", you.first_name);
    printf("Last Name: %s\n", you.last_name);
    printf("Your age %d\n", you.age);
    printf("Your eyecolor %s\n", Eye_Color_Names[you.eyes]);
    printf("Your income %f\n", you.income);

    return 0;
    error:
        return -1;

}

