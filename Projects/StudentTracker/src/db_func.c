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
    db->f = fopen(location,"rb");
    if(!db->f) {log_err("Could not open Database File"); exit(0); }

    int n = sizeof(struct Database)+(sizeof(struct Class)*db->size);
    void *ptr = malloc(n);
    fread(ptr,n,1,db->f);
    ptr+=sizeof(struct Database);

    *db->classes = malloc(n-sizeof(struct Database));
    memcpy(db->classes,ptr,n-sizeof(struct Database));

    if(!db) {log_err("Memmory error"); exit(0);}
    
    fread(db,sizeof(db),1,db->f);
    int size = db->size;

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
    FILE *f = fopen(location,"wb");
    if(!f) {log_err("Could not open Database File"); exit(0); }

    struct Database *db = malloc(sizeof(struct Database));
    if(!db){log_err("Memmory error"); exit(0);}
 
    db->size = 0;

    fwrite(db, sizeof(db),1,f);
    fclose(f);
    free(db);
    exit(1);
    error:
        set_location();
        create_database();
}

void print_database(){
    struct Database *db = open_database();
    log_info("Number of classes is %d",db->size);
    if(db->size != 0){
        for(int i=0;i<db->size;i++){
            log_info("Class %d : %s",i,db->classes[i]->name);
        }

    }
}

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
    log_info("%s",db->classes[0]->name);
    log_info("%s",c->name);

    fwrite(p,n,1,fopen(location,"wb"));
    //free(db);
    //free(p);
}

void print_class(){}