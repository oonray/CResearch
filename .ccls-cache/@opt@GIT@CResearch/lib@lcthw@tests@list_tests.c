#include "minunit.h"
#include "../src/list.h"
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create(){
    list = List_create();
    mu_assert(list != NULL,"Failed To Create List.");
    return NULL;
}

char *test_destroy(){
    List_clear_destroy(list);
    return NULL;
}

char *test_push_pop(){
    List_push(list,test1);
    mu_assert(List_last(list)==test1,"Wrong Last Value.");

    List_push(list,test2);
    mu_assert(List_last(list)==test2,"Wrong Last Value.");

    List_push(list,test3);
    mu_assert(List_last(list)==test3,"Wrong Last Value.");

    char *val=List_pop(list);
    mu_assert(val == test3,"Wrong Pop Value.");

    val=List_pop(list);
    mu_assert(val == test2,"Wrong Pop Value.");
    
    val=List_pop(list);
    mu_assert(val == test1,"Wrong Pop Value.");

    mu_assert(List_count()==0, "Wrong count after pop.");
    return NULL;
}


char *test_unshift(){
    List_unshift(list,test1);
    mu_assert(List_first(list) == test1,"Wrong first value.");

    List_unshift(list,test2);
    mu_assert(List_first(list) == test2,"Wrong first value.");

    List_unshift(list,test3);
    mu_assert(List_first(list) == test3,"Wrong first value.");

    mu_assert(List_count(list)==3,"Wrong count on unshift");
    return NULL;
}

char *test_remove(){
    char  *val = List_remove(list,list->first->next);


}





