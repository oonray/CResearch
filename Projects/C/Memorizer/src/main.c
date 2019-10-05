#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>
#include <json-c/json.h>
#include "cursesdbg.h"
#include "data.h"
#include "curses.h"

#define PATH "data/data.json"

char *banner = "+#########################+\n" "|Welcome To the memorizer!|\n"  "+#########################+\n";
 


int main(int argc, char *argv[]){
		int len;
		int ch = 0;
		char *file;
		char *content;
		struct json_object *parsed;
	   
		init();
		main_win();
		while(ch != 27){		
				debug("lol");
				ch = getch();
		}
		endwin();
		return 0;
		error:
				return 1;
		}
