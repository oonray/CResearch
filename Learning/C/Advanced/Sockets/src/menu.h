//
// Created by oonray on 22.10.2019.
//

#ifndef CHECKLISTS_MENU_H
#define CHECKLISTS_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include "win.h"
#define TYPE_MENU 3

typedef struct{
    int *prev;
    int *next;
    int state;
    char *text;
    win w;
}menrow;

typedef struct{
    int *prev;
    int *next;
    int n;
    menrow *cur;
    win w;
}mencol;

typedef struct{
    int type;
    int border;
    int n;
    mencol *cur;
    win w;
}menu;

mencol *get_last_col(menu m){
    mencol *p = m.cur;
    while((p+1)!=NULL){p=p+1;}
    return p;
}

menrow *get_last_row(mencol mc){
    menrow *p = mc.cur;
    while((p+1)!=NULL){p=p+1;}
    return p;
}


int render_menu(menu m){}
int render_menu_column(mencol mc){}
int render_menu_row(menrow mr){}

menu add_menu_column(menu m, int num, ...){
    va_list columns;
    va_start(columns,num);
    for(int i=0;i<num; i++) {
        mencol *p = va_arg(columns, mencol*);
        mencol *me = get_last_col(m);
        p->prev = me;
        me->next = (int *)p;
    }
    va_end(columns);
    return m;
}

mencol add_menu_column_rows(mencol mc,int num,...){
    va_list rows;
    va_start(rows,num);
    for(int i=0;i<num;i++){
        menrow *p = va_arg(rows,mencol*);
        menrow *me = get_last_row(mc);
        p->prev = me;
        me->next = (int *)p;
    }
    va_end(rows);
    return mc;
}

mencol *make_menu_column(int w,int x,int y){
    mencol *col = (mencol *) malloc(sizeof(mencol));
    col->next = NULL;
    col->prev = NULL;
    col->n=0;
    col->cur=NULL;
    col->w.wid=w;
    col->w.hei=1;
    col->w.x=x;
    col->w.y=y;
    col->w.w=newwin(col->w.hei,col->w.wid,col->w.x,col->w.y);
    wprintw(col->w.w,"Menu",1,0);
}

menrow *make_menu_row(char *text,int w,int x,int y){
    menrow *row = (menrow *) malloc(sizeof(menrow));
    row->next=NULL;
    row->prev=NULL;
    row->state=0;
    row->w.wid=w;
    row->w.hei=1;
    row->w.x =x;
    row->w.y=y;
    row->text = text;
    row->w.w = newwin(row->w.wid,row->w.hei,row->w.x,row->w.y);
    wprintw(row->w.w,row->text,0,1);
}

#endif //CHECKLISTS_MENU_H
