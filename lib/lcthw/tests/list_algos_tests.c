#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char *values[] = {"XXXX","1234","abcd","xjvef","NDDS"};
#define NUM_VALUES 5

List *create_words(){
    List *words = List_create();
    for(int i=0;i<NUM_VALUES;i++){
        List_push(words,values[i]); 
    }
    return words;
}

int is_sorted(List *words){
    LIST_FOREACH(words,first, next, cur){
        if(cur->next && strcmp(cur->value,cur->next->value)>0){
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }
    return 1;
}

char *test_buble_sort(){
    List *words = create_words();
    test_info("Starting Bubble sort test!"); 

    test_info("Starting bubble sort on list!");
    int rc = List_bubble_sort(words,(List_compare) strcmp);
    mu_assert(rc == 0,"Bubble Sort Failed");
    mu_assert(is_sorted(words), "Words Are not Sorted after bubble sort");
    test_sucess("OK. Bubble sort suceeded on list!"); 

    List_destroy(words);
    
    words = List_create(words);
    test_info("Starting Bubble sort on empty list!");
    rc = List_bubble_sort(words,(List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words),"Words should be sorted if empty.");
    test_sucess("OK. Bubble sort suceeded on empty list!");

    List_destroy(words);
    return NULL;
}

char *test_merge_sort(){
    test_info("Starting Merge Sort!");
    List *words = create_words();
    test_info("Words Created!");
    List *res = List_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res),"Words are not sorted after merge sort.");
    test_sucess("OK. Merge sort on list succeeded.");


    List *res2 = List_merge_sort(res, (List_compare) strcmp);
    mu_assert(is_sorted(res),"Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *all_tests(){
    mu_suite_start();
    mu_run_test(test_buble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
