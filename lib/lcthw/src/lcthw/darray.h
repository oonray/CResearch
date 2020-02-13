#ifndef darray_h
#define darray_h

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct Darray{
    int end;
    int max;
    size_t elemen_size;
    size_t expand_rate;
    void **contents;
}Darray;

Darray *Darray_create(size_t elemen_size, size_t initial_max);
void Darray_destroy(Darray *array);
void Darray_clear(Darray *array);
int Darray_expand(Darray *array);
int Darray_contract(Darray *array);
int Darray_push(Darray *array,void *val);
void *Darray_pop(Darray *array);
void *Darrat_clear_destroy(Darray *array);

#define Darray_last(A) ((A)->contents[(A)->end-1])
#define Darray_first(A) ((A)->contents[0])
#define Darray_end(A) ((A)->end)
#define Darray_count(A) Darray_end(A)
#define Darray_max(A) ((A)->max)

static inline void Darray_set(Darray *array,int i,void *val){
    check(i<array->max,"attempt to set darray past max!");
    if(i > array->end){array->end=i;}
    array->contents[i] = val;
error:
    return;
}

static inline void *Darray_get(Darray *array,int i){
    check(i<array->max, "attempt to get past max!");
    return array->contents[i];
error:
    return NULL;
}

static inline void *Darray_remove(Darray *array,int i){ 
    void *el = array->contents[i];
    array->contents[i] = NULL;
    return el;
}

static inline void *Darray_new(Darray *array){
    check(array->elemen_size > 0,"Cant use Darray_new on 0 size darray");
    return calloc(1, array->elemen_size);
error:
    return NULL;
}

#define Darray_free(E) free((E))

#endif
