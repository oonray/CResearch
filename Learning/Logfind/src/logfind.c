
/*

    Usage: logfind <word>

    Searches logfiles for the word. sortof like grep and glob.

    -o uses logical operations.

    output while scanning. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h> 
#include <stdbool.h>

#define allowed_files "~/.logfind"
#define log_dir "/var/log/"
#define MAX_DATA 256

struct Options {
    char *name; 
    char *explenation;
};

struct Names {
    char **directories;
    int num;
    struct dirent *de;
};

struct File {
    char *name;
    FILE *handler;
    char *content;
};

struct FILES {
    struct File *files;
};

struct Names *dir;
struct Names **subdir;
struct Files *files;

struct Options opts[1] = {
    (struct Options){
        .name="-o",
        .explenation="Enables Logical operations in search term."
        }
    };

int get_all_names(char *dir, struct Names *dirs){
    DIR *dr = opendir(dir); 
    if (dr == NULL)  
    { 
        printf("Could not open current directory" ); 
        return 0; 
    }

    while ((dirs->de = readdir(dr)) != NULL){
            int len = sizeof(dirs->de->d_name);
            dirs->directories[dirs->num] = dirs->de->d_name;
            dirs->num++;
    } 

    closedir(dr); 
    return 1;  
}

void get_all_subdir_names(struct Names *dir){
}

void print_directories(struct Names *dirs){
    for(int i=0;i<dirs->num;i++){
        printf("%s\n",dirs->directories[i]);
    }
}


bool string_in_string(char *sub,char *str){
    if(strstr(sub,str) != NULL){
        return true;
    }
    return false;
}

void print_usage(char *program_name){

        printf("This program searches for a words in the log files found in %s\n",log_dir);
        printf("Usage:\n\t%s <searchterm> [options]\n\n",program_name);
        
        for(int i=0; i< sizeof(opts)/sizeof(struct Options);i++){
            struct Options option = opts[i];
            printf("\t %s \t\t %s\n",option.name, option.explenation);
        }

        printf("\n");
}

int main(int argc, char *argv[]){
    if(argc < 2){
        print_usage(argv[0]);
        return 0;
    }
    
    dir = malloc(sizeof(struct Names));
    subdir = malloc(sizeof(struct Names) * MAX_DATA);
    files = malloc(sizeof(struct FILES) * MAX_DATA);

    dir->directories = malloc(sizeof(int) * MAX_DATA);
    printf("%d\n", dir->num);

    get_all_names(log_dir, dir); 
    print_directories(dir);
   
    return 0; 
}