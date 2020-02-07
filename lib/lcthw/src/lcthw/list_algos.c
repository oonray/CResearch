#include "list.h"
#include "list_algos.h"
#include <string.h>

inline int Node_Swap(ListNode *a,ListNode *b){
    void *tmp = a->value;
    a->value = b->value;
    b->value = tmp;
    return 0;
}

int List_bubble_sort(List *list, List_compare comp){
    /*
     * @brief loops and swaps lower items with higher items.
     *
     * Loops over a list, while NOT SORTED sorted.
     *      Swaps higher value list items with lower value list items.
     *
     *  O^n Time
     */
    int sorted = 1;

    if(List_count(list) <= 1){
        return 0;   //0 or 1 Alreaddy sorted
    }

    do {
        sorted = 1;
        LIST_FOREACH(list,first,next,cur){
            if(cur->next){
                if(comp(cur->value,cur->next->value) > 0){
                    Node_Swap(cur,cur->next);
                    sorted = 0;
                }
            }
        }
    } while (!sorted);
    return 0;
}

inline List *List_merge(List *left, List *right, List_compare comp){
    List *result = List_create();
    void *val = NULL;
   
    while(List_count(left) > 0 || List_count(right) > 0){
        if(List_count(left)>0 && List_count(right)>0){
            if(comp(List_first(left),List_first(right))<=0){
                val = List_shift(left); 
            }
            else{
                val = List_shift(right);
            }
            List_push(result,val);
        }
        else if(List_count(left) >0){
            val = List_shift(left);
            List_push(result,val);
        } 
        else if(List_count(right) >0){
            val = List_shift(right);
            List_push(result,val);
        } 
    }
    return result;
}

List *List_merge_sort(List *list, List_compare comp){
    if(List_count(list) <= 1){
        return list; //0 or 1 alreaddy sorted
    } 

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(list)/2;

    LIST_FOREACH(list, first, next, cur){
        if(middle>0){
            List_push(left, cur->value);
        }else{
            List_push(right, cur->value);
        }
        middle--;
    }

    List *sort_left = List_merge_sort(left,comp);   
    List *sort_right = List_merge_sort(right,comp);   

    if(sort_left != left){List_destroy(left);}
    if(sort_right != right){List_destroy(right);}

    return List_merge(sort_left,sort_right,comp);
}
