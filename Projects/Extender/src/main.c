/*
@author Alexander Bjornsrud
@brief A prigram to add extensins to your shells.

*/

#include <stdio.h>
#include <strings.h>
#include "headders/debug.h"

typedef struct node {
    char *val;
    char *exp;
    struct node * next;
} node_t;

char *extensions[9] = {".php5",".pht",".phtml",".shtml",".asa",".cer",".asax",".swf",".xap"};
char *appName;
char *filename;
char *foldername;
char *ext;

node_t *create_args(){
    node_t *head = malloc(sizeof(node_t));
    head->val="-i";
    head->exp="\x1B[32m[Required]\x1B[0m The Input File to copy";
    head->next = malloc(sizeof(node_t));
    head->next->val = "-F";
    head->next->exp = "\x1B[35m[Optional]\x1B[0m The folder to write the files to";
    head->next->next = malloc(sizeof(node_t));
    head->next->next->val = "-e";
    head->next->next->exp = "\x1B[35m[Optional]\x1B[0m The extra Extensions to add seperated by comma";
    return head;
}

int destroy_args(node_t *next){
    if(next->next !=NULL){
        next->next=destroy_args(next->next);
    }
    free(next);
    return NULL;

}

int print_usage(){
    /*
    @brief Prints usage
    Takes the flags and the expleantions and prints a usage message.
    */
   printf("USAGE: %s [option] [value]\n",appName);
   for(int i;i < sizeof(flags)/sizeof(char *); i++){
       printf("\t%s\t%s\n",flags[i],expleantions[i]);
   }
return 0;
}

int check_flag(int argc, char *args[], int flag, char *flags){
    printf("Postion: %i\n", argc);
    printf("Argument: %s\n", args[argc-1]);
    printf("Value: %s\n", args[argc]);


    char * newflags;

    for(int i = flag; i > -1;i--){
        printf("Flag Check: %s\n",flags[i]);
        if(strcmp(args[argc-1],flags[i])==0){
            switch(i){
                case 0:
                    filename = args[argc];
                    break;
                case 1:
                    foldername = args[argc];
                    break;
                case 2:
                    ext = args[argc];
                    break;
                }
            }
    }
    if(argc >= 4){
        check_flag(argc-2,args,flag-1);
    }
}

int main(int argc, char *argv[]){
    appName = argv[0];
    if(argc < 3){
        print_usage();
        return 1;
    }
    check_flag(argc-1,argv,2);
    printf("Filename: %s\n",filename);
    printf("Foldername: %s\n",foldername);
    printf("Extensions: %s\n",ext);
    return 0;
}