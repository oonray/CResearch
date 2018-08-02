#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/constants.h"
#include "inc/debug.h"

void *open_database(){
    check(location,"Location not set. Setting location");
    done:
    FILE *f = fopen(location,"rb");
    if(!f) log_err("Could not open Database File"); exit(0); 

    struct Database *db = malloc(sizeof(struct Database));
    if(!db) log_err("Memmory error"); exit(0);
    
    fread(db,sizeof(struct Database),1,f);
    int size = db->size;
    log_info("The size of the db is %d",size);
    error:
        if(!location){
        set_location();
        goto done;
        }
}

void create_database(){
    check(location,"Location not set. Setting location");
    done:
        FILE *f = fopen(location,"wb");
        if(!f) log_err("Could not open Database File"); exit(0); 

        struct Database *db = malloc(sizeof(struct Database));
        if(!db) log_err("Memmory error"); exit(0);
 
        fwrite(db,sizeof(db),1,f);
        fclose(f);
        exit(1);
    error:
        if(!location){
        set_location();
        goto done;
        }
}
