#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../../../CustomHeadders/colors.h"

int main(int argc, char *argv[]){
    if(argc < 2 || argc > 2){
        printf("%s[-]%s ERROR Wrong amount of inputs!"
               "\n\tUsage: %s <number of bits to shift>",KRED,KNRM,argv[0]);
        return -1;
    }

    int number = 65; //0x01000001
    int shift = atoi(argv[1])
    int num_shift = nuber << shift;
    printf("The number %d shifted by %d is:\n",number,shift);    
}