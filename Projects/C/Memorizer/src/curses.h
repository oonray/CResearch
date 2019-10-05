#include <ncurses.h>

struct main_window{
		WINDOW *w;
		int wid;
		int hei;
		int x;
		int y;
		char border[];
}wmain;

int init(){
		initscr();
//		start_color();
		noecho();
		cbreak();
//		raw();
		keypad(stdscr,TRUE);
		curs_set(0);
		refresh();
		wmain = (struct main_window){NULL,LINES,COLS,0,0}; 
}

int main_win(){
		wmain.w = newwin(wmain.wid,wmain.hei,wmain.x,wmain.y);
		box(wmain.w,0,0);
		wrefresh(wmain.w);

}

