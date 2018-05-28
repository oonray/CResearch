#include <stdio.h>

int main(int argc, char *argv[]){
    char *names[] = { "Alan", "Frank","Mary","Jhon","Lisa" };
    int ages[] = { 23, 43, 12, 89, 2 };
    int count = sizeof(ages)/sizeof(int);

    printf("+--------------------------------+\n");

    for(int i = 0; i < count; i++){
        printf("| %s has lived %d years.\t |\n",names[i],ages[i]);
    }

    printf("+--------------------------------+\n");

    int *cur_age = ages;
    char **cur_name = names;

    for(int i = 0; i<count; i++){
        printf("| %s has lived %d years.\t |\n", *(cur_name+i), *(cur_age+i));
    }

    printf("+--------------------------------+\n");

    for(cur_name = names, cur_age = ages;(cur_age-ages)<count;cur_name++,cur_age++){
        printf("| %s has lived %d years.\t |\n", *cur_name, *cur_age);
    }

    printf("+--------------------------------+\n");

    return 0;
}