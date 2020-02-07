#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "dbg.h"
#include "list.h"
#include <strings.h>

typedef int (*List_compare)(void *,void *);

int List_bubble_sort(List *list, List_compare comp);
List *List_merge_sort(List *list, List_compare comp);

#endif

