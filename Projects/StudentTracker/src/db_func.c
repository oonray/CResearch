#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/constants.h"
#include "inc/debug.h"

char *get_location(){return location;};

void set_location(){
    memcpy(location, argv0, length);
    memcpy(location, strcat(location, DATABASE_FILE), loc_size);    
    };
int get_LSUB(int neg){return LSUB - neg;}
void set_arg0(const char *inp){argv0 = strdup(inp);}
char *get_arg0(){return argv0;}

void *open_database(){
    log_info("Opening Database!");
    check(location,"Location not set. Setting location");
    struct Database *db = malloc(sizeof(struct Database));
    
    int *p = (int *)db;
    
    db->f = fopen(location,"rb");
    if(!db->f) {log_err("Could not open Database File"); exit(0); }

    int n = sizeof(struct Database)+(db->size*sizeof(struct Class));

    void *ptr = malloc(n);
    fread(ptr,n,1,db->f);

    int *ptr_int = (int *)ptr;

    ptr_int = ptr_int + (sizeof(struct Database)/sizeof(int));
    struct Class *cls_ptr = (struct Class *)ptr_int;

    memcpy(db,ptr,sizeof(n));

    db->classes = malloc(db->size*sizeof(struct Class *));

    for(int i = 0; i < db->size;i++){
        db->classes[i] = malloc(sizeof(struct Class));
        memcpy(db->classes[i]->name,"Example",sizeof("Example")/sizeof(char));
    }
    log_info("P pointer is:%d",*p);

    return db;
    error:
        if(!location){
        set_location();
        return open_database();
        }
}

void create_database(){
    log_info("Creating Database!");
    check(location,"Location not set. Setting location");
    struct Database *db = malloc(sizeof(struct Database));

    log_info("Creating databse %s", location);

    db->f = fopen(location,"wb");
    if(!db->f) {log_err("Could not open Database File"); exit(0); }

    if(!db){log_err("Memmory error"); exit(0);}
 
    db->size = 0;

    fwrite(db, sizeof(*db),1,db->f);
    fclose(db->f);
    free(db);
    exit(1);
    error:
        set_location();
        create_database();
};
void print_database(){
    struct Database *db = open_database();
    log_info("Number of classes is %d",db->size);
    if(db->size != 0){
        for(int i=0;i<db->size;i++){
            log_info("Class number %d:",i);
            print_class(db->classes[i]);
        }

    }
};
void add_class(const char *name){
    log_info("Adding Class %s",name);
    struct Database *db = open_database();
    struct Class *new = malloc(sizeof(struct Class));
    db->size += 1;
    new->id = db->size;
    db->f = fopen(location,"wb");
    if((sizeof(name)/sizeof(char)) < (sizeof(new->name)/sizeof(char))){
        memcpy(new->name,name,sizeof(name));
    }else{
        log_err("Name To long!");
        exit(0);
    }

    log_info("Writing to Database!");
    int n = sizeof(db)+(sizeof(struct Class)*db->size);

    void *p = malloc(n);
    struct Class *b = p+1;

    memcpy(p, db, sizeof(db));
    struct Database *p1 = (struct Database *)p;
 
    memcpy(b, db->classes, sizeof(struct Class)*db->size);
    b=b+db->size;
    memcpy(b,new,sizeof(struct Class));

    struct Class *c = (struct Class *)b;
    log_info("DB class 0:%s",db->classes[0]->name);
    log_info("Pointer Name:%s",c->name);

    fclose(db->f);
    FILE *f = fopen(location,"wb");
    fwrite(p1,sizeof(db),1,f);

    free(db);
    free(p);
};
void print_class(struct Class *c){
    log_info("Class  %s",c->name);
}