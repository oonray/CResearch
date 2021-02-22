#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

struct Llist;

typedef struct Llist{
    struct Llist *prev;
    struct Llist *next;
    void    *data;
    size_t  size;
}Llist;

Llist *Llist_New(Llist *prev, void *data, size_t size){
    check(data!=NULL,"Got no data"); 
    Llist *l = (Llist *)calloc(1, sizeof(Llist));
    check_memory(l);

    if(prev != NULL){
        l->prev = prev; 
        prev->next = l;
    }

    l->data = data;
    l->size = size;
    return l;
error:
    return NULL;
}



