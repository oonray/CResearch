#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    int *rt;
    __asm__(
        "mov %0, [gdtr];"
        ".att_syntax;"
        :"=r"(rt));
    printf("%d\n",rt);
}