#ifndef __vector_h
#define __vector_h
#include <stdlib.h>
#include <assert.h>

#include "dbg.h"

typedef struct Vector {
	int end;
	int max;
	size_t element_size;
	size_t expand_rate;
	void **contents;
} Vector;

Vector *Vector_New(size_t element_size,size_t initial_max);
void Vector_Destroy(Vector *arr);
void Vector_Clear(Vector *arr);	

int Vector_Expand(Vector *arr);
int Vector_Contract(Vector *arr);

int Vector_Push(Vector *arr,void *el);
void *Vector_Pop(Vector *arr);

void Vector_Clear_Destroy(Vector *arr);

#define Vector_Last(A) ((A)->contens[(A)->end])
#define Vector_First(A) ((A)->contents[0])
#define Vector_End(A) ((A)->end)
#define Vector_Max(A) ((A)->max)

#define DEFAULT_EXPAND 300

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

static inline void *Vector_Remove(Vector *arr,int i){
	void *el = arr->contents[i]; 
	arr->contents[i] = NULL;
	return el;
}

static inline void *Vector_Create(Vector *arr){
	check(arr->element_size > 0,"Cant Create 0 size Vector");
	return calloc(1,arr->element_size);
error:
	return NULL;
}

#define Vector_Free(E) free((E))
#endif
