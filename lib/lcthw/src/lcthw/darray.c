#include <lcthw/darray.h>
#include <assert.h>

Darray *Darray_create(size_t element_size, size_t initial_max){
    Darray *array = malloc(sizeof(Darray));
    check_mem(array);
    array->max = initial_max;
    check(array->max > 0,"You must set an initial_max > 0");
    
    array->contents = calloc(initial_max,sizeof(void *));
    check_mem(array->contents);
    
    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;
        
error:
    if(array){free(array);}
    return NULL;

}

void Darray_clear(Darray *array){
    if(array->element_size > 0){
        for(int i = 0;i<array->max;i++){
            if(array->contents[i]!=NULL){
                free(array->contents[i]);
            }
        }
    }
}

static inline int Darray_resize(Darray *array,size_t newsize){
    array->max = newsize;
    check(array->max > 0, "The newsize must be > 0");
    
    void *contents = realloc(array->contents, array->max * sizeof(void *));
    check_mem(contents);

    array->contents = contents;
    return 0; 

error:
    return -1;
}

int Darray_expand(Darray *array){
   size_t old_max = array->max;
   int exp = array->max+array->expand_rate;
   check(Darray_resize(array,exp)==0,"Failed to expand array to size %d",exp);
    
   memset(array->contents + old_max,0,array->expand_rate+1);
   return 0;
error:
   return -1;
}

int Darray_contract(Darray *array){
    int new_size = array->end < (int)array ->expand_rate ? (int) array->expand_rate : array->end;
    return Darray_resize(array, new_size+1);
}

void Darray_destroy(Darray *array){
    if(array){
        if(array->contents){
            free(array->contents);
        }
        free(array);
    }
}

void *Darray_clear_destroy(Darray *array){
    Darray_clear(array);
    Darray_destroy(array);
}


int Darray_push(Darray *array, void *val){
    array->contents[array->end] = val;
    array->end++;

    if(Darray_end(array) >= Darray_max(array)){
        return Darray_expand(array);
    }else{
        return 0;
    }

}

void *Darray_pop(Darray *array){
    check(array->end -1 >=0, "Attempt to pop on empty array!");
    void *val = Darray_remove(array, array->end -1);
    array->end--;

    if(Darray_end(array)>(int)array->expand_rate && Darray_end(array)%array->expand_rate){
        Darray_contract(array);
    }
    return val;
error:
    return NULL;
}
