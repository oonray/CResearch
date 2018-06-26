#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef (*math)(int a, int b);

struct Operation{
    char *name;
    int inp1;
    int inp2;
    math action;
};

void die(const char *message){
    if(errno) perror(message);
    else printf("ERROR: %s",message);
    exit(0);
}

int pluss(int a, int b){
    return a+b;
}

int subtract(int a, int b){
    return a-b;
}

int multiply(int a,int b){
    return a*b;
}

int devide(int a, int b){
    return a/b;
}

int domath(struct Operation *input){
    printf("Result of %s %d to %d is %d\n",input->name,input->inp1,input->inp2,input->action(input->inp1,input->inp2));
}

int main(int argc, char *argv[]){
    if(argc < 4) die("To Few Argumetns. Minimum 3");
    struct Operation *action = malloc(sizeof(struct Operation));
    action->name = strdup(argv[1]);
    action->inp1 = atoi(argv[2]);
    action->inp2 = atoi(argv[3]);

    char name = argv[1][0];

    switch(name){
        case 'P':
        case 'p':
            action->action = &pluss;
            break;
        case 'S':
        case 's':
           action->action = &subtract;
           break;
        case 'M':
        case 'm':
            action->action = &multiply;
            break;
        case 'D':
        case 'd':
            action->action = &devide;
            break;
        default:
            die("First Argument must be: Pluss, Subtract, Multiplay or Devide");
            break;
    }

    domath(action);
    free(action);

    return 1;
}