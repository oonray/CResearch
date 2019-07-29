/*
 * Header file for findfiles
 * Dan Gookin, LinkedIn Learning, Code Clinic 2018
 */

/************** INCLUDES **************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
/* Ensure that you specify the proper path to wherever your system
   hides the curl and libjpeg eader files */
#include <curl/curl.h>
#include <jpeglib.h>

/************** DEFINES **************/
/* use the system's maximum filename length - if defined */
#ifndef NAME_MAX
#define NAME_MAX 256
#endif

/* enumerated constants for identifying graphics file type */
enum { JPEG=1, JPG, GIF, PNG };

/*
 * preset information about Watson
 * Sign up for a free Watson API / IBM Cloud account at:
 * https://www.ibm.com/watson/services/visual-recognition/demo/index.html#watson-demo
 * REMEMBER: Replace the WATSON_API_KEY	value below with your account's API_KEY
 */
#define WATSON_ADDRESS_PREFIX "https://gateway-a.watsonplatform.net/visual-recognition/api/v3/detect_faces?api_key="
#define WATSON_API_KEY "{set your api key here}"
#define WATSON_ADDRESS_SUFFIX "&version=2018-03-19"

/************** STRUCTURES **************/
struct coordinates {
	int height;
	int width;
	int left;
	int top;
};
struct picture {
	char filename[NAME_MAX];
	int facecount;
	struct coordinates *locations;
};
struct web_data {
	char *buffer;
	size_t size;
};
struct square {
	unsigned char *buffer;
	struct jpeg_decompress_struct info;
	int row;
	int col;
	int width;
	int height;
};
struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

/************** PROTOTYPES **************/

int file_extension(char *filename);
int get_line(char *s);
void extract_faces(char *j);
int grab(char *s,char *v);
void reduce(char *a, char **b);
char *examine_image(char *filename);
int watson(void);
void process_jpeg(void);
char *build_output_filename(char *ifn);
void highlight_square(struct square b);
void draw_square(struct square bc,struct color c);

