#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;

};

void die(const char message){
    if(errno){
        perror(message);
    }else{
        printf("ERROR: %s\n",message);
    }
    exit(1);
}

void Address_Print(struct Address *addr){
    printf("%s: \n\t %s\n",addr->name,addr->email);
}

void Database_load(struct Connection *conn){
    int rc = fread(conn->db, sizeof(struct Database),1,conn->file);
    if(rc != 1)
        die("Faild to load database");
}

struct Connection *database_open(const char *filename,char mode){
    struct Connection *conn = malloc(sizeof(struct Database));
    if(!conn)
        die("Memmory Error!");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db)
        die("Memmory erroor");
    
    if(mode == 'c'){
        conn->file = fopen(filename, "w");
    }else{
        conn->file = fopen(filename,"r+");
        if(conn->file){
            Database_load(conn);
        }
    }

    if(!conn->file)
        die("Failed to open File");
    
    return conn;
}

void Database_close(struct Connection *conn){
        if(conn){
            if(conn->file)
                fclose(conn->file);
            if(conn->db)
                free(conn->db);
            free(conn);
        }
}

void Database_write(struct Connection *conn){
    rewind(conn->file);
    int rc = fwrite(conn->db,sizeof(struct Database),1,conn->file);
    if(rc != 1)
        die("Failed to write to DB");

    rc = fflush(conn->file);
    if(rc == -1)
        die("Cannot flush database");
}

void Database_create(struct Connection *conn){
    for(int i=0;i<MAX_ROWS;i++){
        struct Address addr = { .id=i, .set=0 };
        conn->db->rows[i]=addr;
    }
    
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
        die("Alreaddy set, delte it first!");
    addr->set = 1;
    char *res = strncpy(addr->name, email, MAX_DATA);
    if(!res)
        die("Name Copy Failed!");
        
}

void Database_get(struct Connection *conn,int id){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set){
        Address_Print(addr);
    }else{
        die("ID is not set!");
    }
}

void Database_list(struct Connection *conn){
    struct Database *db = conn->db;
    for(int i = 0; i < MAX_ROWS;i++){
        struct Address *cur = &db->rows[i];
        if(cur->set){
            Address_Print(cur);
        }
    }
}

