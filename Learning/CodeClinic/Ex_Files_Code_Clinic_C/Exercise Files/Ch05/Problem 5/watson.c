#include "findfaces.h"

extern int verbose;
extern struct picture image;

static size_t write_mem(void *ptr, size_t size, size_t nmemb, void *userdata);

int watson(void)
{
	char *json_data_raw,*json_data_reduced;

	json_data_raw = examine_image(image.filename);
	if(verbose)
	{
		printf("Raw JSON data:\n%s\n",json_data_raw);
	}
	reduce(json_data_raw,&json_data_reduced);
	extract_faces(json_data_reduced);

	/* print JSON output */
	/* I faked this as well because I've yet to see a good,
	   tight JSON library */
	printf("{\n\t\"countFaces:\" : %d,\n",image.facecount);
	printf("\t\"imageLocation\" : \"%s\"\n}\n",image.filename);

	return(image.facecount);
}

/*
 * Pull in each instance of the 'face_location' array in the JSON
 * data buffer. Beacuse I detest the C language JSON libraries, this
 * function is a kludge to extract the array and save it locally.
 * The array is then crunched and the coordinates extracts and
 * saved to the coordinates structure. I'd prefer to use a JSON
 * library but they are poorly documented and supported.
 */
void extract_faces(char *j)
{
	char subcoords[128];
	char *base,*jp;
	int offset;

	/* initialize the base pointer*/
	base = j;

	/* initially test for a Watson error */
	if(strstr(j,"\"error\":")!=NULL)
	{
		jp = strstr(j,"description\":");
		jp+=13;
		while(*jp!='\"')
			jp++;
		jp++;
		printf("Watson has reported an error: ");
		while(*jp!='\"')
		{
			putchar(*jp);
			jp++;
		}
		putchar('\n');
		exit(0);
	}

	if(verbose)
	{
		puts("Processing received data...");
	}

	/* repeatedly scan the json string for 'face_location' */
	while(1)
	{
		/* search for the first instance of 'face_location' */
		jp = strstr(base,"face_location");
			/* if not found, stop the loop */
		if(jp==NULL)
			break;
		
		/* and allocate the structure */
		/* remember: facecount==0 the first spin, so add 1 */
		image.locations = (struct coordinates *)realloc(image.locations,sizeof(struct coordinates)*(image.facecount+1));
		if(image.locations==NULL)
		{
			fprintf(stderr,"Unable to reallocate structure\n");
			exit(1);
		}

		/* extract the object's pairs to the subcoords[] buffer */
			/* search for the first brace */
		while(*jp!='{')
			jp++;
			/* and copy the guts to subcoords */
		offset=0;
		while( *(jp+offset) != '}')
		{
			subcoords[offset] = *(jp+offset);
			offset++;
		}
		/* cap the string */
		*(jp+offset) = '\0';
		/* reset the base for the next loop */
		base = jp+offset+1;

		/* grab the values */
		/* The values are stored in the coordinates structure referenced
		   by 'face'. The offsets are calculated in a way to fake a
		   dynamic array. The ** pointer notation gets really ugly here,
		   but it works and allows you to modify the pointer set in another
		   function */
		(image.locations+image.facecount)->height = grab(subcoords,"height");
		(image.locations+image.facecount)->width = grab(subcoords,"width");
		(image.locations+image.facecount)->left = grab(subcoords,"left");
		(image.locations+image.facecount)->top = grab(subcoords,"top");

		/* increment the counter */
		image.facecount++;
	}
}

/*
 * This cheesy little function searches for a given string, effectively
 * a JSON array key. It then locates the first digit after the key and
 * returns the integer value.
 */
int grab(char *s,char *v)
{
	char *index;

	index = strstr(s,v);
	while(!isdigit(*index))
		index++;
	return(atoi(index));
}

/*
 * Remove extra spaces and newlines from raw json data
 * For some reason, the extract_faces() function choked on the raw data
 * read from Watson. If I remove the extra spaces and newlines from that
 * data, extract_faces() works properly. So I wrote this code to reduce
 * the multi-line, indended JSON data to a single line.
 */
void reduce(char *a, char **b)
{
	char *temp;
	int len,y,z;

	/* allocate temporary storage */
	len = strlen(a);
	temp=(char *)malloc( sizeof(char)*len+1 );
	if(temp==NULL)
	{
		fprintf(stderr,"Unable to allocate temporary storage\n");
		exit(1);
	}

	/* copy and reduce the buffer */
		/* I need 2 index variables, one for each buffer */
	y = z = 0;
	while(*(a+z) != '\0')
	{
		/* when two spaces occur, skip the first one */
		if( *(a+z)==' ' && *(a+z+1)==' ')
		{
			z++;
		}
		/* for any newline (not the last one), skip */
		else if( *(a+z)=='\n' && *(a+z+1)!='\0')
		{
			z++;
		}
		/* copy the character */
		else
		{
			*(temp+y) = *(a+z);
			y++;
			z++;
		}
	}
	/* terminate the string */
	*(temp+y) = '\0';

	/* allocate and return the result */
	*b = (char *)malloc(strlen(temp)+1);
	if(*b==NULL)
	{
		fprintf(stderr,"Couldn't even allocate the passed buffer\n");
		exit(1);
	}
	strcpy(*b,temp);
	
	free(temp);
}

/*
 * Visit the Watson site to submit an image file and obtain
 * JSON data regarding faces in the file. You must have an IBM Cloud
 * account and API_KEY to access this feature, as described at the
 * top of this code. The file is uploaded via POST form submission.
 * JSON data is really extensive.
 * This function is static to retain the JSON buffer read.
 */
char *examine_image(char *filename)
{
	CURL *curl;
	CURLcode res;
	char *address;
	curl_mime *form = NULL;
	curl_mimepart *field = NULL;
	static struct web_data page;

	/* allocate storage */
		/* for web data structure */
	page.buffer = malloc(1);
	page.size = 0;
		/* for Watson's address */
	address = (char *)malloc(
			strlen(WATSON_ADDRESS_PREFIX)+
			strlen(WATSON_API_KEY)+
			strlen(WATSON_ADDRESS_SUFFIX)+
			1 );
	if(address==NULL)
	{
		fprintf(stderr,"Unable to allocate Watson address storage buffer\n");
		exit(1);
	}

	if(verbose)
	{
		puts("Uploading image file to Watson...");
	}

	/* initialuze curl */
	curl = curl_easy_init();

	/* build address string */
	strcpy(address,WATSON_ADDRESS_PREFIX);
	strcat(address,WATSON_API_KEY);		/* This must be assigned! */
	strcat(address,WATSON_ADDRESS_SUFFIX);

	/* create form and data */
	/* The curl command line uses: -X POST --form "image_files@filename"
	   The following lines emulate these options in libcurl */
	form = curl_mime_init(curl);
	field = curl_mime_addpart(form);
	curl_mime_name(field,"images_file");
	curl_mime_filedata(field,filename);

	/* set curl options */
		/* setup the form for submission */
	curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
		/* point to the memory-writing function */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page);
		/* set the URL */
	curl_easy_setopt(curl, CURLOPT_URL, address);
	
	/* read the address */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		fprintf(stderr,"curl read failed: %s\n",
				curl_easy_strerror(res));
		exit(1);
	}
	
	/* clean up */
	curl_easy_cleanup(curl);
	curl_mime_free(form);

	return(page.buffer);
}

/*
 * Libcurl function to copy bytes read from the web page to memory
 * This is the typical memory-writing function used in curl coding.
 * Information is read in chunks and appended to a buffer. This function
 * may be called repeatedly, which is why it's static, to retain the
 * web_data structure's buffer and size values.
 */
static size_t write_mem(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize;
	struct web_data *mem;

	realsize = size * nmemb;
	mem = (struct web_data *)userdata;

	mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);
	if(mem->buffer == NULL)
	{
		fprintf(stderr,"Unable to reallocate buffer\n");
		exit(1);
	}

	memcpy(&(mem->buffer[mem->size]),ptr,realsize);
	mem->size += realsize;
	mem->buffer[mem->size] = 0;

	return(realsize);
}

