#include "munit.h"
#include "map.h"

typedef struct TestData{
	int traverse_called;
	char *data1;
	char *data2;
	char *data3;
	char *expect1;
	char *expect2;
	char *expect3;
	Map *map;
}TestData;

TestData *TestData_New(){
		TestData *t = calloc(1,sizeof(TestData));
		t->map = NULL;
		t->traverse_called = 0;
		t->data1 = "Test data 1";
		t->data2 = "Test data 2";
		t->data3 = "Test data 3";
		t->expect1 = "The VALUE 1";
		t->expect2 = "The VALUE 2";
		t->expect3 = "The VALUE 3";
		return t;
}

static int Traverse_Success_Func(Map_Node *node){
	log_info("KEY: %s",(char *)node->key);
	return 0;	
}

static int Traverse_Fail_Func(Map_Node *node){
	log_info("KEY: %s",(char *)node->key);
	return 1;	
}

static void *setup(){
		return TestData_New();
}

MunitResult test_new(const MunitParameter params[], void* user_data_or_fixture){
		TestData *dt = user_data_or_fixture; 	
		dt->map = Map_New(NULL,NULL);
		check(dt->map != NULL, "Could not create map");
		free(dt->map);
		free(dt);
		return MUNIT_OK;
error:
		return MUNIT_FAIL;
}

MunitResult test_destroy(const MunitParameter params[], void* user_data_or_fixture){
		TestData *dt = user_data_or_fixture; 	
		dt->map = Map_New(NULL,NULL);
		check(dt->map != NULL, "Could not create map");

		Map_Destroy(dt->map);
		free(dt);
		return MUNIT_OK;
error:
		return MUNIT_FAIL;
}

MunitResult test_get_set(const MunitParameter params[], void* user_data_or_fixture){
		TestData *dt = user_data_or_fixture; 	
		dt->map = Map_New(NULL,NULL);


		check(dt->map != NULL, "Could not create map");

		int rc = Map_Set(dt->map,&dt->data1,&dt->expect1);
		check(rc == 0,"Failed to set data1");

		rc = Map_Set(dt->map,&dt->data2,&dt->expect2);
		check(rc == 0,"Failed to set data2");
		
		rc = Map_Set(dt->map,&dt->data3,&dt->expect3);
		check(rc == 0,"Failed to set data3");


		return MUNIT_OK;
error:
		return MUNIT_FAIL;
}

int main(int argc, char *const *argv){
	MunitTest tests[] = {
		{" test_new",test_new,setup,NULL,MUNIT_TEST_OPTION_NONE,NULL},
		{" test_destroy",test_destroy,setup,NULL,MUNIT_TEST_OPTION_NONE,NULL},
		{NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
	};
	
	const MunitSuite suite ={
		"Map Tests",
		tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE
	};

	return munit_suite_main(&suite, NULL,0,NULL);
}


