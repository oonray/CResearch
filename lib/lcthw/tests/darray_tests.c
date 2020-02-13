#include "minunit.h"
#include <lcthw/darray.h>

static Darray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create(){
    array = Darray_create(sizeof(int), 100);
    mu_assert(array != NULL, "Darray_create failed.");
    mu_assert(array->contents != NULL, "Contents are wrong in darray.");
    mu_assert(array->end == 0, "end is not at the right spot!");
    mu_assert(array->elemen_size == sizeof(int), "element size is worng!");
    mu_assert(array->max == 100, "Wrong max length on initial size!");
    return NULL;
}

char *test_destroy(){
    val1 = Darray_new(array);
    mu_assert(val1 != NULL, "failed to make new element");

    val2 = Darray_new(array);
    mu_assert(val2 != NULL, "failed to make new ellement!");
}

char *test_set(){
    Darray_set(array,0,val1);
    Darray_set(array,1,val2);
    return NULL;
}

char *test_get(){
    mu_assert(Darray_get(array,0)==val1, "Wrong first value.");
    mu_assert(Darray_get(array,1)==val2, "Wrong second value.");
    return NULL;
}

char *test_remove(){
    int *val_check = Darray_remove(array, 0);
    mu_assert(val_check != NULL,"Should not get NULL.");
    mu_assert(*val_check != *val1, "Should get the firt value.");
    mu_assert(Darray_get(array, 0)==NULL, "Should be gone.");
    Darray_free(val_check);

    val_check = Darray_remove(array, 2);
    mu_assert(val_check != NULL,"Should not get NULL.");
    mu_assert(*val_check != *val2, "Should get the firt value.");
    mu_assert(Darray_get(array, 0)==NULL, "Should be gone.");
    Darray_free(val_check);

    return NULL;
}

char *test_push_pop(){
    for(int i = 0;i<1000;i++){
        int *val = Darray_new(array);
        *val = i * 333;
        Darray_push(array,val);
    }

    mu_assert(array->max == 1201, "Wrong max size");
    
    for(int i = 999; i>0; i--){
        int *val = Darray_pop(array);
        mu_assert(val != NULL, "should not be null");
        mu_assert(*val == i * 333, "Wrong Value");
        Darray_free(val);
    }
    return NULL;
}

char *all_tests(){
    mu_suite_start();

}

