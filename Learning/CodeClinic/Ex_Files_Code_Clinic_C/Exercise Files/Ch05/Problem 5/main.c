/*
 * Code Clinic 2018, Problem 5, C language
 * Dan Gookin
 * Accept a JPEG, GIF, or PNG image and identify the number of faces.
 * The function returns the number of faces or zero
 * Create a copy of the image with the faces identified
 * Generate JSON output with two fields: countFaces and imageLocation (filename)
 */

#include "findfaces.h"

int verbose;
struct picture image;

int main(int argc, char *argv[])
{
	int r;

	/* initialize data */
	image.locations = malloc(1);
	image.facecount = 0;

	/* handle any command line options */
	/* prompt for input if filename argument unavailable */
	if(argc<2)
	{
		printf("Image filename: ");
		if( get_line(image.filename) == 0 )
			exit(1);
	}
	else
	{
		strcpy(image.filename,argv[1]);
	}
	if(argc==3)
	{
		if(strcmp(argv[2],"--verbose")==0)
			verbose=1;
		else
			verbose=0;
	}

	/* detect filename extension and process file */
	switch(file_extension(image.filename))
	{
		case JPEG:
		case JPG:
			if(verbose)
			{
				printf("%s identified as a JPEG image\n",image.filename);
			}
			r = watson();
			if(r > 0)
				process_jpeg();
			break;
		case GIF:
			if(verbose)
			{
				printf("%s identified as a GIF image\n",image.filename);
			}
			watson();
			break;
		case PNG:
			if(verbose)
			{
				printf("%s identified as a PNG image\n",image.filename);
			}
			watson();
			break;
		default:
			printf("Unrecognized or invalid image filename extension\n");
	}

	return(0);
}

/*
 * Given a string 'filename' return the extension value
 * Return values are enumerated: JPEG=1, JPG=2, GIF=3; PNG=4
 * Return value of 0 indicates invalid or missing filename extension
 */
int file_extension(char *filename)
{
    char *ext;
	int len;

	/* allocate storage */
	ext = (char *)malloc( sizeof(char) * 5);
	if(ext==NULL)
	{
		fprintf(stderr,"Unable to allocate memory\n");
		exit(1);
	}
	
	/* find the end of the string */
    len = strlen(filename);
	/* if empty string, return zero */
    if( len == 0 )
        return(0);

	/* find the terminating separator */
    ext = filename+len;
    while( *ext != '.')
    {
        ext--;
        /* don't go too far! */
        if( ext < filename+len-5 )
            return(0);
    }
    ext++;    /* increment beyond the separator */

	/* catch no filename condition */
    if( *ext == '\0')
        return(0);

	/* compare extension with known graphics filetype extesnions */
	if(strcasecmp(ext,"JPEG")==0)
		return(JPEG);
	else if(strcasecmp(ext,"JPG")==0)
		return(JPG);
	else if(strcasecmp(ext,"GIF")==0)
		return(GIF);
	else if(strcasecmp(ext,"PNG")==0)
		return(PNG);
	else
		return(0);
}

/*
 * Read a line of text. Essentially this is the fgets() function
 * but it also removes any trailing newline from the input string
 */
int get_line(char *s)
{
	int x;

	fgets(s,NAME_MAX,stdin);
	for(x=0;x<NAME_MAX;x++)
	{
		if( *(s+x)=='\n')
		{
			*(s+x)='\0';
			return(x);
		}
	}
	return(x);
}

