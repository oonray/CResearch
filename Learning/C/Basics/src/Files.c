#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){

    char *filepath = "files/Files.txt";
    char *message = "Hello World!";
    char *buff = malloc(sizeof(char));

    FILE *f = fopen(filepath,"w");
    fpos_t p = 4;
    long p_;

    fwrite(message,strlen(message),1,f);
    fclose(f);

    freopen(filepath,"r",f);

    fsetpos(f,&p);

    fread(buff,1,1,f);
    printf("At position %lld: %s\n",p,buff);

    fseek(f,3,SEEK_CUR);
    p_ = ftell(f);

    fread(buff,1,1,f);
    printf("At position %ld: %s\n",p_,buff);

    freopen(filepath,"a",f);

    fprintf(f,"\n%s",message);
    free(buff);

    freopen(filepath,"r",f);

    buff = malloc(sizeof(char));
    
    rewind(f);
    p_ = ftell(f);
    fread(buff,1,1,f);
    printf("After Rewind %ld: %s\n",p_,buff);
    free(buff);
    fclose(f);

    



}