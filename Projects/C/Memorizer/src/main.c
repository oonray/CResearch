#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>
#include <json-c/json.h>
#include "dbg.h"

#define CATEGORIES 1
#define BLOCK 1024
#define PATH "data/data.json"

char *banner = "+#########################+\n" "|Welcome To the memorizer!|\n"  "+#########################+\n";
 


int main(int argc, char *argv[]){
		char *file;

		printf("%s\n",banner);
		char *content = read_input_file(PATH);
		check(content,"File not read");
		
		struct json_object *parsed = json_tokener_parse(content);
	
		return 0;
		error:
				return 1;
}
