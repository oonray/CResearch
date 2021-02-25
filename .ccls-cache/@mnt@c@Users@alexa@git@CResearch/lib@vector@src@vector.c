#include "vector.h" 
#include <assert.h>

Vector *Vector_New(size_t element_size,size_t initial_max){
		Vector *arr = malloc(sizeof(Vector));
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

void Vector_Clear(Vector *arr){
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

int Vector_Expand(Vector *arr){
		size_t old_max = arr->max;
		int exp = arr->max+arr->expand_rate;

		check(Vector_Resize(arr,exp)==0,"Faild to expand vector to %d",exp);
		memset(arr->contents + old_max,0,arr->expand_rate+1);
		return 0;
error:
		return -1;
}

int Vector_Contract(Vector *arr){
	int new_size = arr->end < (int)arr->expand_rate ? (int)arr->expand_rate : arr->end;
	return Vector_Resize(arr,new_size + 1);	
}

void Vector_Destroy(Vector *arr){
		if(arr){
			if(arr->contents){
				free(arr->contents);
				free(arr);
			}
		}
}

void Vector_Clear_Destroy(Vector *arr){
		Vector_Clear(arr);
		Vector_Destroy(arr);
}

int Vector_Push(Vector *arr,void *el){
	arr->contents[arr->end] = el;	
	arr->end++;
	if(Vector_End(arr)>=Vector_Max(arr)){
			return Vector_Expand(arr);
	}
	return 0;
}

void *Vector_Pop(Vector *arr){
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
