/*
 * Code Clinic 2018, Problem 2, C language
 * Dan Gookin
 * Based on the system's external IP address, return the longitude and
 * lattitude. Express its accuracy as a radius measured in kilometers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* Ensure that you specify the proper path to wherever your system
   hides the curl header files */
#include <curl/curl.h>

#define BUFSIZE 256

/* standard data-chunk-reading structure used by libcurl */
struct web_data {
	char *buffer;
	size_t size;
};
/* structure to store web page information */
struct location {
	char address[BUFSIZE];
	double latitude;
	double longitude;
};

void parse(char *json, char *key, char *val);
void fetch(int v, char *o,char *f);
static size_t write_mem(void *ptr, size_t size, size_t nmemb, void *userdata);

int main()
{
	CURL *curl;
	CURLcode res;
	char csv_field[BUFSIZE],ip[BUFSIZE],value[BUFSIZE];
	char *offset;
	int x;
	double avg_lon,avg_lat,tot_lon,tot_lat,max_lon,max_lat,rad_lon,rad_lat,radius;
	struct location url[3];
	struct web_data curl_data[3];

	/* initialize structure */
	/* curl_data and url structures must be kept separate or the
	   call the curl makes to write_mem() screws up */
	for(x=0;x<3;x++)
	{
		curl_data[x].buffer = malloc(1);
		curl_data[x].size = 0;
		url[x].latitude = 0.0;
		url[x].longitude = 0.0;
	}
	/* initialize locations */
	strcpy(url[0].address,"http://ip-api.com/csv/");
	strcpy(url[1].address,"https://tools.keycdn.com/geo.json?host=");
	strcpy(url[2].address,"https://ipinfo.io/");

	/* initialuze curl */
	/* I use the same curl handle for all of the calls,
	   so only only statement is needed here */
	curl = curl_easy_init();

	/*---------------- FIRST READ ----------------*/
	/* set options */
		/* url to read */
	curl_easy_setopt(curl, CURLOPT_URL, url[0].address);
		/* The function to read in data chunks */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
		/* The structure to use for reading */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_data[0]);
	/* make the call */
	res = curl_easy_perform(curl);
	/* confirm that the call was successful, bail if not */
	if( res != CURLE_OK )
	{
		fprintf(stderr,"Curl read failed: %s\n",
				curl_easy_strerror(res)
			   );
		exit(1);
	}

	/* At this point, the size of the data read is stored in curl_data.size
	   and the string read is in curl_data.buffer. The data is in CSV format,
	   which the fetch() function can read */
	/* was the call successful? Fetch the first CSV item from the buffer and
	   store it in buffer 'csv_field' */
	fetch(1,curl_data[0].buffer,csv_field);
	/* if the string csv_field isn't 'success' then the call failed */
	if( strncmp(csv_field,"success",7) != 0 )
	{
		fprintf(stderr,"Failed request from server: %s\n",url[0].address);
		fprintf(stderr,"Retried status: %s\n",csv_field);
		exit(1);
	}

	/* Get the latitude value & convert to double */
	fetch(8,curl_data[0].buffer,csv_field);
	url[0].latitude = strtod(csv_field,NULL);

	/* Get the longitude value & convert to double */
	fetch(9,curl_data[0].buffer,csv_field);
	url[0].longitude = strtod(csv_field,NULL);

	/* also fetch this system's Internet IP for use in the next call */
	fetch(14,curl_data[0].buffer,ip);

	/*---------------- SECOND READ ----------------*/
	/* reset curl and start over */
	curl_easy_reset(curl);
	
	/* first, append the IP address to the URL */
	strcat(url[1].address,ip);
	/* configure the call */
	curl_easy_setopt(curl, CURLOPT_URL, url[1].address);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_data[1]);
	/* read the page */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		fprintf(stderr,"curl read failed: %s\n",
				curl_easy_strerror(res)
			   );
		exit(1);
	}

	/* The buffer now contains JSON data for the given IP */
	/* confirm that the call was successful */
	parse(curl_data[1].buffer,"status",value);
	if( strcmp(value,"success")==0 )
	{
		/* extract the latitude key */
		parse(curl_data[1].buffer,"latitude",value);
		url[1].latitude = strtod(value,NULL);
		/* extract the longitude key */
		parse(curl_data[1].buffer,"longitude",value);
		url[1].longitude = strtod(value,NULL);
	}
	else
	{
		printf("Read from site %s unsuccessful\n",url[1].address);
	}
	
	/*---------------- THIRD READ ----------------*/
	/* reset curl to do it one more time */
	curl_easy_reset(curl);

	/* append the IP to the address */
	strcat(url[2].address,ip);
	/* and append the json string to the address */
	strcat(url[2].address,"/json");
	/* configure the call */
	curl_easy_setopt(curl, CURLOPT_URL, url[2].address);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_data[2]);
	/* read the page */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		fprintf(stderr,"curl read failed: %s\n",
				curl_easy_strerror(res)
			   );
		exit(1);
	}

	/* page buffer contains json data. Looking for the key "loc" */
	parse(curl_data[2].buffer,"loc",value);
	/* key loc has two values, separated by a comma as in "0.0,0.0" */
		/* find the comma */
	offset = value;
	while(*offset!=',')
	{
		if(*offset=='\0')
		{
			fprintf(stderr,"Unable to parse 'loc' data\n");
			exit(1);
		}
		offset++;
	}
	/* cap the first string (latitude) and point offset at the second, longitude */
	*offset='\0';
	offset++;
	url[2].latitude = strtod(value,NULL);
	url[2].longitude = strtod(offset,NULL);
	
	/* quit curl */
	curl_easy_cleanup(curl);
	
	/*---------------- PROCESS AND DISPLAY RESULTS ----------------*/
	/* Difference between latitude lines is 60 nautical miles, or 111.12 kilometers.
	   For longitude, the value changes as it gets closer to the poles:
	   1 deg of longitude = cos(latitude)*111 kilometers at the equator.
	   Values are approximate because Earth isn't a perfect sphere. */
	/* My method here is to average all the latitude and longitude values, then
	   determine the farthest distance from that average. I use this farthest
	   value (latitude or longitude) to set the accuracy radius in kilometers.
	   Yes, this may not be a cartographically proper solution, but all this data
	   is guesswork anyway. */

	/* Obtain the average latitude and longitude values */
	tot_lon = tot_lat = 0.0;
	for(x=0;x<3;x++)
	{
		tot_lat+=url[x].latitude;
		tot_lon+=url[x].longitude;
	}
	avg_lat = tot_lat/3.0;
	avg_lon = tot_lon/3.0;

	/* which longitude and latitude items are farthest from the average? */
	max_lon = max_lat = 0.0;
	for(x=0;x<3;x++)
	{
		max_lon = max_lon < fabs(avg_lon)-fabs(url[x].longitude) ? fabs(avg_lon)-fabs(url[x].longitude) : max_lon;
		max_lat = max_lat < fabs(avg_lat)-fabs(url[x].latitude) ? fabs(avg_lat)-fabs(url[x].latitude) : max_lat;
	}

	/* set the distance of max_lon and max_lat in kilometers
	   and set the maximum as the radius value. Degrees-to-radians
	   calculation uses 0.0174532925 */
	rad_lon = max_lon*cos(avg_lat*0.0174532925)*111.12;
	rad_lat = max_lat*111.12;
	radius = rad_lon >= rad_lat ? rad_lon : rad_lat;

	/* display results */
	printf("Data for IP address %s:\n",ip);
	printf("%s\t%s\t%s\n",
			"Site",
			"Latitude",
			"Longitude"
		  );
	for(x=0;x<3;x++)
	{
		printf("%3d\t%f\t%f\n",
				x+1,
				url[x].latitude,
				url[x].longitude
			  );
	}
	printf("Accuracy is within a radius of %f kilometers\n",radius);

	return(0);
}

/*
 * Rather than suffer through lots of bulky code to read JSON data
 * I kludged a routine to fetch key-value details. By no means should
 * this code be used to parse other JSON structures, though it came in
 * handy here for this specific purpose.
 */
void parse(char *json, char *key, char *val)
{
	char *found,*size;
	int x;

	/* locate the string and add its length, plus one for the double quote */
	found = strstr(json,key)+1;
	/* find the colon */
	while(*found!=':')
	{
		if(*found=='\0')
		{
			fprintf(stderr,"Unable to parse value for '%s'\n",key);
			exit(1);
		}
		found++;
	}
	/* find the next character after the second double quote */
	while(*found!='\"')
	{
		if(*found=='\0')
		{
			fprintf(stderr,"Unable to parse value for '%s'\n",key);
			exit(1);
		}
		found++;
	}
	/* and skip past the double quote */
	found++;

	/* find the end of the value */
	size = found+1;
	while(*size != '\"')
	{
		if(*size=='\0')
		{
			fprintf(stderr,"Unable to parse value for '%s'\n",key);
			exit(1);
		}
		size++;
	}

	/* copy the string */
	x = 0;
	*val='\0';
	while(*(found+x) != '\"')
	{
		if(*(found+x)=='\0')
		{
			fprintf(stderr,"Malformed json value\n");
			exit(1);
		}
		*(val+x) = *(found+x);
		x++;
	}
	/* cap with a null character */
	*(val+x) = '\0';
}

/*
 * Return a specific item from the csv string
 * v is the item number to read, from 1 up to whatever. The csv string
 * is referenced by *csv. *f is the buffer to contain the found data.
 * Data is created locally in buffer[], then copied to *f.
 * Modified so that the result value isn't returned and if the field
 * isn't available, the program quits within the function.
 */
void fetch(int v, char *csv, char *f)
{
	char buffer[BUFSIZE];
	char *b,*cptr;
	int bi,count;

	/* ensure that v is valid */
	if(v<1)
	{
		fprintf(stderr,"Inavlid field for CSV string\n");
		exit(1);
	}

	/* scan for valid fields and pull them out */
	cptr = csv;
	b = buffer;
	bi = 0;
	count = 1;
	while(*cptr)
	{
		/* start copying characters */
		*(b+bi) = *(cptr);
		/* if a quoted string is encountered, copy it all over */
		if(*(b+bi)=='"')
		{
			/* skip over the comma as it's not really part of the string */
			/* Do this by resetting bi to -1, which then increments to zero
			   with the next statement */
			bi = -1;
			do
			{
				bi++;
				cptr++;
				if(bi>BUFSIZE)
				{
					fprintf(stderr,"Malformed CSV field\n");
					exit(1);
				}
				*(b+bi) = *(cptr);
			} while(*(b+bi)!='"');
			/* skip over the final double quote */
			cptr++;
		}
		/* when the comma is encountered, a field has ended */
		if(*cptr==',')
		{
			if(count==v)
			{
				/* cap the string */
				*(b+bi) = '\0';
				strcpy(f,buffer);
				return;
			}
			else
			{
				/* up the count and reset bi */
				count++;
				bi=-1;
			}
		}
		bi++;
		cptr++;
		/* check for buffer overflow */
		if(bi>BUFSIZE)
			break;
	}
	/* check to see whether it's the final item */
	if(count==v)
	{
		*(b+(bi))='\0';
		strcpy(f,buffer);
		return;
	}

	/* if we get here, there was some sort of error */
	fprintf(stderr,"Unable to read field %d from CSV record\n",v);
	exit(1);
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

