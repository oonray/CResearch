#include "../minunit.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *data);

char *lib_file = "bin/mylib.so";

void *lib =NULL;

int check_function(const char *func_to_run, const char *data, int excpected){
		lib_function func = dlsym(lib, func_to_run);
		check(func != NULL, "Did not find %s function in the library %s: %s",func_to_run, lib_file, dlerror());
		int rc = func(data);
		check(rc == excpected,"function %s returned %d for data: %s",func_to_run,data);
		return 1;
error:
		return 0;}

char *test_dlopen(){ 
		lib = dlopen(lib_file,RTLD_NOW);
		mu_assert(lib != NULL,"Failed to open the library!");
		return NULL;}


char *test_functions(){
		mu_assert(check_function("a_message","Hello",0),"a_message failed");
		mu_assert(check_function("uppercase","Hello",0),"uppercase failed");
		mu_assert(check_function("lowercase","Hello",0),"lowercase failed");
		//mu_assert(check_function("fail_on_purpouse","Hello",0),"fail_on_purpouse failed");
		return NULL;}

char *test_failures(){return NULL;}

char *test_dlclose(){return NULL;}

char *all_tests(){
		mu_suite_start();
		mu_run_test(test_dlopen);
		mu_run_test(test_functions);
//		mu_run_test(test_failures);
//		mu_run_test(test_dlclose);
		return NULL;}

RUN_TESTS(all_tests);
