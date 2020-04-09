#include <lcthw/darray_algos.h>
#include <stdlib.h>

int Darray_qsort(Darray *array, Darray_compare cmp){
    qsort(array->contents, Darray_count(array), sizeof(void *),cmp);
    return 0;
}

int Darray_heapsort(Darray *array, Darray_compare cmp){
    return heapsort(array->contents,Darray_count(array),sizeof(void *),cmp); 
}

int Darray_mergesort(Darray *array, Darray_compare cmp){
    return mergesort(array->contents,Darray_count(array),sizeof(void *),cmp);
}
