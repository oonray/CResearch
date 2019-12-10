#ifndef __dbg_h__
#define __dbg_h__
#endif

#include <stdio.h>
#include <errno.h> 
#include <string.h>
#include <ncurses.h>

struct error_window{
		WINDOW *w;
		int wid;
		int hei;
		int x;
		int y;	
}werr;

#define log(M,T,...){\
		werr.hei=5;\
		werr.wid=50;\
		werr.x=(LINES-werr.hei)/2;\
		werr.y=(COLS-werr.wid)/2; \
		werr.w = newwin(werr.hei,werr.wid,werr.x,werr.y);\
		mvwprintw(werr.w,2,2,"[.] %s:%d:%s: %s",__FILE__,__LINE__,__func__,M,##__VA_ARGS__);\
		mvprintw(werr.x,werr.y+1,T);\
		box(werr.w,0,0);\
		wrefresh(werr.w);\
		getch();\
		wrefresh(werr.w);\
		wclear(werr.w);\
		refresh();\
}\

#define error(M,E,...){\
		werr.hei=5;\
		werr.wid=50;\
		werr.x=(LINES-werr.hei)/2;\
		werr.y=(COLS-werr.wid)/2; \
		werr.w = newwin(werr.hei,werr.wid,werr.x,werr.y);\
		mvwprintw(werr.w,2,2,"[!] %s:%d:%s: errno: %s %s",__FILE__,__LINE__,__func__,E,M,##__VA_ARGS__);\
		mvprintw(werr.x,werr.y+1,"Error!");\
		box(werr.w,0,0);\
		wrefresh(werr.w);\
		getch();\
		wrefresh(werr.w);\
		wclear(werr.w);\
		refresh();\
}\


#define debug(M,...) log(M,"Debug",##__VA_ARGS__)
#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_err(M,...) error(M,clean_errno(),##__VA_ARGS__);
#define check(A,M, ...) if(!(A)) {log_err(M,##__VA_ARGS__);errno=0;goto error;}

