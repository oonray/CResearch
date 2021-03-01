#ifndef __vector_h
#define __vector_h
#include <stdlib.h>
#include <assert.h>

#include "dbg.h"

typedef int (Vector_Traverse_Func)(void *);

typedef struct Vector {
	int end;
	int max;
	size_t element_size;
	size_t expand_rate;
	void **contents;
} Vector;

#define Vector_Last(A) ((A)->contens[(A)->end])
#define Vector_First(A) ((A)->contents[0])
#define Vector_End(A) ((A)->end)
#define Vector_Max(A) ((A)->max)

#define DEFAULT_EXPAND 300

static inline Vector *Vector_New(size_t element_size,size_t initial_max){
		Vector *arr = (Vector *)malloc(sizeof(Vector));
		check_memory(arr);

		arr->max = initial_max;
		check(arr->max > 0, "There must be an initial max");

		arr->contents = calloc(initial_max,sizeof(void *));
		check_memory(arr->contents);

		arr->end = 0;
		arr->element_size = element_size;

		arr->expand_rate = DEFAULT_EXPAND;
		return arr;
error:
		if(arr){
			free(arr);
		}
		return NULL;
} 

static inline void Vector_Destroy(Vector *arr){
		if(arr){
			if(arr->contents){
				free(arr->contents);
				free(arr);
			}
		}
}

static inline void Vector_Clear(Vector *arr){
	int i = 0;
	if(arr->element_size > 0){
		for(i = 0; i < arr->max; i++){
				if(arr->contents[i] != NULL){
						free(arr->contents[i]);
				}
		}
	}
}

static inline int Vector_Resize(Vector *arr,size_t new_size){
		arr->max = new_size;
		check(arr->max > 0,"The max size must be grater than 0");

		void *content = realloc(arr->contents,arr->max*sizeof(void *));
		check_memory(content);

		arr->contents = content;
		return 0;
error:
		return -1;
}

static inline int Vector_Expand(Vector *arr){
		size_t old_max = arr->max;
		int exp = arr->max+arr->expand_rate;

		check(Vector_Resize(arr,exp)==0,"Faild to expand vector to %d",exp);
		memset(arr->contents + old_max,0,arr->expand_rate+1);
		return 0;
error:
		return -1;
}

static inline int Vector_Contract(Vector *arr){
	int new_size = arr->end < (int)arr->expand_rate ? (int)arr->expand_rate : arr->end;
	return Vector_Resize(arr,new_size + 1);	
}

static inline int Vector_Push(Vector *arr,void *el){
	arr->contents[arr->end] = el;	
	arr->end++;
	if(Vector_End(arr)>=Vector_Max(arr)){
			return Vector_Expand(arr);
	}
	return 0;
}

static inline void *Vector_Remove(Vector *arr,int i){
	void *el = arr->contents[i]; 
	arr->contents[i] = NULL;
	return el;
}

static inline void *Vector_Pop(Vector *arr){
		check(arr->end-1>=0,"Cannot pop from Empty");	
		void *el = Vector_Remove(arr,arr->end-1);
		arr->end--;

		if((Vector_End(arr)>(int)arr->expand_rate)&&(Vector_End(arr)%arr->expand_rate)){
			Vector_Contract(arr);
		}
		return el;
error:
		return NULL;
}

static inline void Vector_Clear_Destroy(Vector *arr){
		Vector_Clear(arr);
		Vector_Destroy(arr);
}

static inline void Vector_Set(Vector *arr,int i, void *el){
		check(i < arr->max,"Attempt to set beyond max");
		if(i > arr->end){
				arr->end = i;
		}
		arr->contents[i] = el;
error:
		return;
}

static inline void *Vector_Get(Vector *arr,int i){
	check(i < arr->max,"Atempting to get beyond max");
	return arr->contents[i];
error:
	return NULL;
}


static inline void *Vector_Create(Vector *arr){
	check(arr->element_size > 0,"Cant Create 0 size Vector");
	return calloc(1,arr->element_size);
error:
	return NULL;
}

#define Vector_Free(E) free((E))
#endif
