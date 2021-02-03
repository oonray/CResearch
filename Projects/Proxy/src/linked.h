#include <stdio.h>
#include "dbg.h"

struct Llist;

typedef struct Llist{
    struct Llist *prev;
    struct Llist *next;
    void    *data;
    size_t  *size;
}Llist;

Llist *Llist_New(Llist *prev,void *data){
    check(data!=NULL,"Got no data"); 

    if(prev == NULL){}
error:
    return NULL;
}
