struct data{
		int num_categories;
		struct json_object categories;
		struct json_object data;
}data;

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

struct json_object *get_n_categories(struct json_object *json){
		/*
		 *@name get_categories 
		 *@param struct json_object json
		 *@brief gets the question categories
		 */
		struct json_object *ncategories;
		json_object_object_get_ex(json,"ncategories",&ncategories); 
		return ncategories;
}

struct json_object *get_categories(struct json_object *json){
		/*
		 *@name get_categories 
		 *@param struct json_object json
		 *@brief gets the question categories
		 */
		struct json_object *categories;
		json_object_object_get_ex(json,"categories",&categories); 
		return categories;
}

