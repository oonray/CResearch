#include <stdio.h>
#include <dlfcn.h>

int main(int args, char *argv[]){
       if(argc != 4){
        info("USAGE: %s *.so",argv[0]);
        return 1;
    }

    char *lib_file = argv[1];
    void *lib = dlopen(lib_file, RTLD_NOW);
    return 0;
}