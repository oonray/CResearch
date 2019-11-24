//
// Created by oonray on 22.10.2019.
//

#ifndef CHECKLISTS_WIN_H
#define CHECKLISTS_WIN_H
#include "ncurses.h"
#define TYPE_WINDOW 1

typedef struct{
    int *prev;
    int *next;
    int type;
    WINDOW *w;
    int wid;
    int hei;
    int x;
    int y;
}win;

int *get_last_item(int *start){
    int *p = start;
    while((p+2)!=NULL){p=p+2;}
    return p;
}

#endif //CHECKLISTS_WIN_H
