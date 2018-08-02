#include <stdlib.h>
#include <stdint.h>
#include "inc/debug.h"
#include "inc/constants.h"


int main(int argc, char *argv[]){  
    if(argc <= 1){
        sentinel("To Few Arguments!");
    }
    set_arg0(argv[0]);

    if(argv[0][strlen(argv[0])-1] != 'e'){length = strlen(argv[0])-get_LSUB(4);}
    else{length = strlen(argv[0])-get_LSUB(0);}

    loc_size = (length * sizeof(char)) + (sizeof(DATABASE_FILE)/sizeof(char));
    location = malloc(loc_size);
    
    check_mem(location);

    set_location();

    struct Arg1 i_target[4] = 
        { 
            { .name = "-cd", .position = 1, .func = &create_database}, 
            { .name = "-pd", .position = 1, .func = &print_database},
            { .name = "-ac", .position = 2, .func = &add_class },
            { .name = "-pc", .position = 1, .func = &print_class }
        };
    
    struct Arg2 i_2_target[1] =
        { 
            {}
        };

    for(int i = 0;i < 4;i++){
        if(strcmp(argv[1], i_target[i].name) == 0){
            if(i_target[i].position > 1){
                i_target[i].func(argv[2]);
            }else{
                i_target[i].func("");
            }
        }
    }
    

    return 1;
    error:
        return 0;
}


