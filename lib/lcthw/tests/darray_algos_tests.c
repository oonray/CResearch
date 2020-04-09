#include "lcthw/darray.h"
#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b){
    return strcmp(*a,*b);
}

Darray *create_words(){
    Darray *result = Darray_create(0, 5);
    char *words[] = {"asdfasfd","werwar","123456","fasdfasd","oioi"};
    
    for(int i = 0; i < 5; i++){
        Darray_push(result,words[i]);
    }

    return result;
}

int is_sorted(Darray *array){
    for(int i = 0;i<Darray_count(array)-1;i++){
        if(strcmp(Darray_get(array,i),Darray_get(array,i+1))>0){
            return 0;
        }
    }
    return 1;
}

char *run_sort_test(int (*func) (Darray *,Darray_compare), const char *name){
    Darray *words = create_words();
    mu_assert(!is_sorted(words), "Words should start not sorted");
    
    debug("--- Testing %s sorting Algo",name);
    int rc = func(words,(Darray_compare) testcmp);
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted(words), "did not sort it");

    Darray_destroy(words);
    return NULL;
}

char *test_qsort(){
    return run_sort_test(Darray_qsort, "qsort");
}

char *test_heapsort(){
    return run_sort_test(Darray_heapsort,"heapsort");
}

char *test_mergesort(){
    return run_sort_test(Darray_mergesort,"mergesort");
}

char *all_tests(){
    mu_suite_start();
    mu_run_test(test_qsort);
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);
    return NULL;
}

RUN_TESTS(all_tests);
