#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>


Bstree *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");

struct tagbstring expect1 = bsStatic("The Value 1");
struct tagbstring expect2 = bsStatic("The Value 2");
struct tagbstring expect3 = bsStatic("The Value 3");

static int traverse_good_cb(BstreeNode *node){
    debug("KEY: %s",bdata((bstring) node->key));
    traverse_called++;
    return 0;

}

static int traverse_fail_cb(BstreeNode *node){
    debug("KEY: %s",bdata((bstring)node->key));
    traverse_called++;

    if(traverse_called==2){
        return 1;
    }else{
        return 0;
    }
}

char *test_create(){
    map = Bstree_create(NULL);
    mu_assert(map != NULL,"Failed to create map.");

    return NULL;
}

char *test_destroy(){
    Bstree_destroy(map);
    return NULL;
}

char *test_get_set(){
    int rc = Bstree_set(map,&test1,&expect1);
    mu_assert(rc == 0,"Failed to set test1");

    bstring result = Bstree_get(map,&test1);
    mu_assert(result==&expect1,"Wrong value for test1.");


    rc = Bstree_set(map,&test2,&expect2);
    mu_assert(rc == 0,"Failed to set test2");

    result = Bstree_get(map,&test2);
    mu_assert(result==&expect2,"Wrong value for test2.");

    rc = Bstree_set(map,&test3,&expect3);
    mu_assert(rc == 0,"Failed to set test3");

    result = Bstree_get(map,&test3);
    mu_assert(result==&expect3,"Wrong value for test3.");

    return NULL;
}


char *test_traverse(){
    int rc = Bstree_traverse(map,traverse_good_cb);
    mu_assert(rc == 0,"Failed to traverse.");
    mu_assert(traverse_called == 3,"Wrong count traverse.");

    traverse_called = 0;
    rc = Bstree_traverse(map,traverse_fail_cb);
    mu_assert(rc==1,"Failed to traverse.");
    mu_assert(traverse_called == 2,"Wrong count for traverse fail");

    return NULL;
}

char *test_delete(){
    bstring deleted = (bstring)Bstree_delete(map,&test1);
    mu_assert(deleted != NULL,"Got NULL on delte.");
    mu_assert(deleted == &expect1,"Should get test1");
    bstring result = Bstree_get(map,&test1);
    mu_assert(result == NULL,"Should delete");
}

char *test_fuzzing(){
    Bstree *store = Bstree_create(NULL);
    int i = 0;
    int j = 0;
    bstring numbers[100] = {NULL};
    bstring data[100] = {NULL};
    srand((unsigned int )time(NULL));

    for(i = 0;i<100;i++){
        int num = rand();
        numbers[i] = bformat("%d",num);
        data[i] = bformat("data %d",num);
        Bstree_set(store,numbers[i],data[i]);
    }

    for(i=0;i<100;i++){
        bstring value = Bstree_delete(store,numbers[i]);
        mu_assert(value == data[i],"Failed to delete right number");
        test_info("%s",(char *)value);

        mu_assert(Bstree_delete(store,numbers[i])==NULL,"Should be deleted.");

        for(j = 0;j<99;j++){
            bstring value = Bstree_get(store,numbers[j]); 
            mu_assert(value == data[j],"Failed to get the right number.");

        }
        bdestroy(value);
        bdestroy(numbers[i]);
    }

    Bstree_destroy(store);
    return NULL;
}

char *all_tests(){
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);
//    mu_run_test(test_fuzzing);
    
    return NULL;
}

RUN_TESTS(all_tests);
