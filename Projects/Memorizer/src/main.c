#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include<json-c/json.h>
#include "dbg.h"

#define CATEGORIES 1
#define BLOCK 1024
#define PATH "data/data.json"

char *banner = "+#########################+\n" "|Welcome To the memorizer!|\n"  "+#########################+\n";
 
char *read_input_file(char *path){
		FILE *fp = fopen(path,"r");
		check(fp,"File could not be opened!");
		uint32_t reads = 0;
		char *out;

		char *buff = malloc(BLOCK);
		while(fread(buff,1,BLOCK,fp)){
				strcat(out,buff);
				reads++;
		};	
		
		log_info("Read %d times\n",reads);

		return out;
		error:
				return NULL;
}

int main(int argc, char *argv[]){
		char *file;
		uint32_t n_categories;
		uint32_t n_questons[CATEGORIES];
		uint32_t n_question;

		struct json_object *category;
		struct json_object *questions;
		struct json_object *answers;
		
		struct json_object *question;
		struct json_object *answer;

		printf("%s\n",banner);
		char *content = read_input_file(PATH);
		check(content,"File not read");
		printf("%s\n",content);
		return 0;
		error:
				return 1;
}
