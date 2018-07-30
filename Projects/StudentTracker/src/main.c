#include <stdlib.h>
#include <stdint.h>

#include "inc/debug.h"

#include "inc/constants.h"

char *location;

typedef void (*function)(const char *inp);

struct Arg1{
    char *name;
    int position;
    function func;
};

struct Arg2{
    char *name;
    char *value;
};

void create_database(const char *inp){

    log_info("Crating DB\n");
    log_info("Folder: %s\n", location);
    
    FILE *file = fopen(location,"wb");
    fclose(file);
    
}

int set_argument1(struct Arg1 *target,const char *name, int position, function func){
    target->name = strdup(name);
    target->position = position;
    target->func = func;
}

int set_argument2(struct Arg2 *target,const char *name, const char *value){
    target->name = strdup(name);
    target->value = strdup(value);
}

int main(int argc, char *argv[]){  
    if(argc <= 1){
        sentinel("To Few Arguments!");
    }

    int lsub = 18;
    int length = strlen(argv[0])-lsub;
    int loc_size = (length * sizeof(char)) + (sizeof(DATABASE_FILE)/sizeof(char));
    
    location = malloc(loc_size);
    
    if(!location){
        sentinel("Out Of Memory!");
    }

    memcpy(location, argv[0],length);
    memcpy(location,strcat(location, DATABASE_FILE), loc_size);
    
    struct Arg1 *i_target[2] = 
        { 
            malloc(sizeof(struct Arg1)), 
            malloc(sizeof(struct Arg1))
        };
    
    struct Arg2 *i_2_target[1] =
        { 
            malloc(sizeof(struct Arg2))
        };

    set_argument1(i_target[0], "-cd", 1, &create_database);
    if(argc>2){
        set_argument2(i_2_target[0], "-c", argv[3]);
    }

    if(strcmp(argv[1], i_target[0]->name) == 0){
        char *extra_arg = "";
        if(argc>2){
            if(strcmp(argv[2], i_2_target[0]->name) == 0){
                extra_arg = i_2_target[0]->value;
            }
        }
        i_target[0]->func(extra_arg);
    }

    return 1;
    error:
        return 0;
}

