#include "headders/structs.h"

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage:\n\tOpens a file and reads the PE propperties\n\t%s\t<name of file>",argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1],"rb");


}