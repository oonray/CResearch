#include <ncurses.h>

struct main_window{
		WINDOW w;
		int width;
		int height;
		int start;
		int end;
		char border[];
} wmain = {LINES,COLS,0,0};

int init(){
		initscr();
		noecho();
		cbreak();
//		raw();
		keypad(stdscr,TRUE);
		refresh();
}

int main_win(){
		wmain.w = newwin(wmain.width,wmain.height,wmain.start,wmain.end);
		wrefresh(wmain.w);

}

