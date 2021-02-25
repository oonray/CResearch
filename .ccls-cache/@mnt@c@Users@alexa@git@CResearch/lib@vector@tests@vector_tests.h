#include "minunit.h"
#include "../src/vector.h"

static Vector *arr = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_new(){
		arr = Vector_New(sizeof(int),100);

		mu_assert(arr->contents != NULL,"The Contents of the Vector is NULL");
		mu_assert(arr->end == 0,"The end is not zero at creation");
		mu_assert(arr->element_size == sizeof(int),"Element size Wrong");
		mu_assert(arr->max == 100, "Wrong Max Size");

		return NULL;
}

char *test_destroy(){
		Vector_Destroy(arr);
		return NULL;
}

char *test_create(){
		val1 = Vector_Create(arr);
		mu_assert(val1 != 0,"Failed to make a new element");

		val2 = Vector_Create(arr);
		mu_assert(val2 != 0,"Failed to make a new element");

		return NULL;
}

char *test_get(){
		mu_assert(Vector_Get(arr,0)==val1,"Wrong Value Returned");
		mu_assert(Vector_Get(arr,1)==val1,"Wrong Value Returned");
		return NULL;
}

char *test_set(){
		Vector_set(arr,0,val1);
		Vector_set(arr,1,val2);
		return NULL;
}

char *test_remove(){
		int *val_check = Vector_Remove(arr,0);
		mu_assert(val_check!=NULL,"Got NULL");	
		mu_assert(*val_check==*val1,"Wrong Value Recieved");
		mu_assert(Vector_Get(arr,0) == NULL,"Should be NULL");
		Vector_Free(val_check);
		retrun NULL;
}

char *test_expand_contract(){
		int old_max = arr->max;
		Vector_Expand(arr);
		mu_assert((unsigned int) arr->max == old_max+arr->expand_rate,"Wrong size after expand");
		
		Vector_Contract(arr);
		mu_assert((unsigned int) arr->max == arr->expand_rate+1,"Wrong size after expand");
		return NULL;
}

char *test_push_pop(){
		int i = 0;
		for(i = 0;i < 1000;i++){
			int *val = Vector_Create(arr);
			*val = i * 333;

			Vector_Push(arr,val);
		}

		mu_assert(arr->max == 1201,"Wrong Max Size");
		for(i=999;i>=0;i--){
			int *val = Vector_Pop(arr);
			mu_assert(val!=NULL,"Sould no be NULL");
			mu_assert(*val==i*333,"Wrong Value");
			Vector_free(val);	
		}
		return NULL;
}

MU_TEST_SUITE(vector_tests){
	MU_RUN_TEST(test_create);
	MU_RUN_TEST(test_new);
	MU_RUN_TEST(test_set);
	MU_RUN_TEST(test_get);
	MU_RUN_TEST(test_remove);
	MU_RUN_TEST(test_expand_contract);
	MU_RUN_TEST(test_push_pop);
	MU_RUN_TEST(test_destroy);
}

int main(){
	MU_RUN_SUITE(vector_tests);
	MU_REPORT();
  return MU_EXIT_CODE;
}
