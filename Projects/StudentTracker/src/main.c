#include <stdlib.h>
#include <stdint.h>

#include "inc/debug.h"
#include "inc/constants.h"
#include "argparser.c"

int LSUB;
char *location;
int length;
int loc_size;


void create_database(const char *inp){

    log_info("Crating DB\n");
    log_info("Folder: %s\n", location);
    
    FILE *file = fopen(location,"wb");
    struct Database *db = alloc_db();
    check_mem(db);
    db->size = 0;
    fwrite(db,sizeof(struct Database),1,file);
    fclose(file);
    free_db(db);
    error:
        log_err("Database Error!");
}

void write_database(struct Class *the_new_class){
    FILE *file = fopen(location, "rb");
    
    struct Database *db = alloc_db();
    check_mem(db);
    fread(db,sizeof(struct Database),1,file);
    memcpy(db->classes[db->size+1], the_new_class ,sizeof(struct Class));
    db->size++;
    fwrite(db,sizeof(db),1,file);
    fclose(file);
    error:
        log_err("Write error!");
}

int main(int argc, char *argv[]){  
    if(argc <= 1){
        sentinel("To Few Arguments!");
    }

    if(argv[0][strlen(argv[0])-1] != 'e'){set_LSUB(4);}
    length = strlen(argv[0])-LSUB;
    loc_size = (length * sizeof(char)) + (sizeof(DATABASE_FILE)/sizeof(char));
    location = malloc(loc_size);
    
    check_mem(location);

    set_location(argv[0]);

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
    if(argc > 2){
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


