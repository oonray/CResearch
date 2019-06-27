/**
 * @file main.c
 * @author Alexander Bjørnsrud (alexanderbjornsrud@gmail.com)
 * @brief Runs a function from DLL
 * @version 0.1
 * @date 2019-04-27
 * 
 * @copyright Copyright (c) 2019
 * 
 * This Program Loads a DLL and calls a function From it.
 * Modified form Learn C the Hard Way code.
 */
#include <stdio.h>
#include <dlfcn.h>
#include "headders/colors.h"
#include "headders/debug.h"

typedef int (*lib_function)(const char *data); //Function Definition

int main(int argc, char *argv[]){
    /**
     * @brief The main function.
     * 
     */
    int rc = 0;
    
    if(argc != 4){
        info("USAGE: %s *.so <function> <data>",argv[0]);
        return 1;
    }
    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    void *lib = dlopen(lib_file, RTLD_NOW); //loads DLL
    if(lib == NULL){
        error("Faled To open %s : %s",lib_file,dlerror());
        return 1;
    }
    lib_function func = dlsym(lib,func_to_run); //loads Function
    rc = func(data);

    if(rc != 0){
        error("Failed to run %s :code %d width data %s",func_to_run,rc,data);
        return 1;
    }
    return 0;
}