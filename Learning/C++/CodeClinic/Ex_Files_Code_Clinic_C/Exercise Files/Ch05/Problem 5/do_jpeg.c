#include "findfaces.h"

extern int verbose;
extern struct picture image;

/*
 * This is a standard JPEG reading-writing function
 * The output is compressed, so the resulting file is smaller.
 * The code uses the coordinates passed to draw boxes around each
 * found face.
 * This code doesn't account for EXIF rotation data. That would be a
 * whole 'nuther nut to crack, so if the final image is incorrectly
 * oriented, it's because the rotation data isn't retained. The boxes
 * appear in the right spots, but the underlying image is rotation-
 * corrected.
 */
void process_jpeg(void)
{
	FILE *original,*duplicate;
	char *out_filename;
	struct jpeg_decompress_struct dcinfo;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr dcjerr;
	struct jpeg_error_mgr cjerr;
	unsigned char *raw_image;
	JSAMPROW row_pointer[1];
	unsigned long location,row_stride;
	int i;
	struct square box;

	/* open the input file */
	original = fopen(image.filename,"rb");
	if(!original)
	{
		printf("Unable to open file '%s'\n",image.filename);
		exit(1);
	}

	/* configure libjpeg */
	dcinfo.err = jpeg_std_error(&dcjerr);
	jpeg_create_decompress(&dcinfo);
	jpeg_stdio_src(&dcinfo,original);
	jpeg_read_header(&dcinfo,TRUE);
	jpeg_start_decompress(&dcinfo);
	
	/* Create buffers for the uncompressed data */
	raw_image = (unsigned char *)malloc(dcinfo.output_width*dcinfo.output_height*dcinfo.num_components);
	row_pointer[0] = (unsigned char *)malloc(dcinfo.output_width*dcinfo.num_components);
	if(raw_image==NULL || row_pointer[0]==NULL)
	{
		fprintf(stderr,"Unable to allocate memory for image");
		fclose(original);
		exit(1);
	}
	
	/* loop to read each scanline and store it in the buffer */
	location = 0;
	while(dcinfo.output_scanline < dcinfo.output_height)
	{
		jpeg_read_scanlines(&dcinfo,row_pointer,1);
		for(i=0;i<dcinfo.image_width*dcinfo.num_components;i++)
		{
			*(raw_image+location) = row_pointer[0][i];
			location++;
		}
	}

	/* raw image is stored in the buffer raw_image */
	/* cleanup and close */
	jpeg_finish_decompress(&dcinfo);
	free(row_pointer[0]);
	fclose(original);

	/* For each face found, draw a highlight box at a given location */
	for(i=0;i<image.facecount;i++)
	{
		box.buffer = raw_image;
		box.info = dcinfo;
		box.row = (image.locations+i)->top;
		box.col = (image.locations+i)->left;
		box.width = (image.locations+i)->width;
		box.height = (image.locations+i)->height;
		highlight_square(box);
	}

	/* Compress and save the data into a new file */
	out_filename = build_output_filename(image.filename);

	/* Raw data remains in the raw_image buffer. */
	/* Open file for output. No checking is done to ensure
	   that the file doesn't already exist */
	duplicate = fopen(out_filename,"wb");
	if(!duplicate)
	{
		fprintf(stderr,"Unable to create output image file.\n");
		exit(1);
	}

	/* prep libjpeg to compress raw image data */
	cinfo.err = jpeg_std_error(&cjerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo,duplicate);
	cinfo.image_width = dcinfo.output_width;
	cinfo.image_height = dcinfo.output_height;
	cinfo.input_components = dcinfo.num_components;
	cinfo.in_color_space = dcinfo.out_color_space;
	jpeg_set_defaults(&cinfo);
	/* Begin compression */
	jpeg_start_compress(&cinfo,TRUE);
	/* write one scanline at a time */
	while(cinfo.next_scanline < cinfo.image_height)
	{
		row_stride=cinfo.next_scanline*cinfo.image_width*cinfo.input_components;
		row_pointer[0] = (raw_image+row_stride);
		jpeg_write_scanlines(&cinfo,row_pointer,1);
	}

	/* clean-up */
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	jpeg_destroy_decompress(&dcinfo);
	fclose(duplicate);

	if(verbose)
	{
		printf("Output file '%s' created\n",out_filename);
	}
}

/*
 * Create modified filename, adding suffix "-faces" and retaining
 * the original JPG or JPEG extension
 */
char *build_output_filename(char *ifn)
{
	static char *newname;
	char *extension;
	char suffix[] = "-faces";
	int len,x;

	len = strlen(ifn);
	/* first check for JPG */
	extension = strcasestr(ifn,".jpg");
	/* then check for JPEG */
	if(extension==NULL)
	{
		extension = strcasestr(ifn,".jpeg");
		if(extension==NULL)
		{
			fprintf(stderr,"Is %s really a JPEG file? It's missing the extension\n",
					ifn
				   );
			exit(1);
		}
	}

	/* process the new filename */
	newname = (char *)malloc(len+strlen(suffix)+strlen(extension)+1);
	if(newname==NULL)
	{
		fprintf(stderr,"Filename memory allocation failed\n");
		exit(1);
	}
	/* copy over the first part */
	for(x=0;x<(int)(extension-ifn);x++)
		*(newname+x) = *(ifn+x);
	/* terminate the string */
	*(newname+x) = '\0';
	/* append the suffix and original extension */
	strcat(newname,suffix);
	strcat(newname,extension);

	return(newname);
}

void highlight_square(struct square b)
{
	struct color black = { 0, 0, 0 };
	struct color white = { 255, 255, 255 };

	if(b.col+b.width > b.info.output_width || b.row+b.height > b.info.output_height)
	{
		puts("square is off the grid");
		exit(1);
	}
	if(b.width < 10 || b.height < 10)
	{
		puts("square is too small");
		exit(1);
	}

	draw_square(b,black);
	b.row++;
	b.col++;
	b.width-=2;
	b.height-=2;
	draw_square(b,white);
	b.row++;
	b.col++;
	b.width-=2;
	b.height-=2;
	draw_square(b,black);
}

void draw_square(struct square bc,struct color c)
{
	unsigned char *top_row_base,*bottom_row_base;
	int tbref,lref,rref;
	int i; 

	bc.col *= 3;
	top_row_base = bc.buffer+(bc.info.output_width * 3 * bc.row);
	bottom_row_base = bc.buffer+(bc.info.output_width * 3 * (bc.row+bc.height));
	for(i=0; i<bc.width*3; i+=3)
	{
		tbref = bc.col+i;
		/* top */
		*(top_row_base+tbref+0) = c.r;			/* red */
		*(top_row_base+tbref+1) = c.g;			/* green */
		*(top_row_base+tbref+2) = c.b;			/* blue */
		/* bottom */
		*(bottom_row_base+tbref+0) = c.r;		/* red */
		*(bottom_row_base+tbref+1) = c.g;		/* green */
		*(bottom_row_base+tbref+2) = c.b;		/* blue */
	}
	for(i=0;i<bc.height;i++)
	{
		lref = bc.info.output_width*3*i+bc.col;
		rref = bc.info.output_width*3*i+bc.col+bc.width*3;
		/* left */
		*(top_row_base+lref+0) = c.r;			/* red */
		*(top_row_base+lref+1) = c.g;			/* green */
		*(top_row_base+lref+2) = c.b;			/* blue */
		/* right */
		*(top_row_base+rref+0) = c.r;			/* red */
		*(top_row_base+rref+1) = c.g;			/* blue */
		*(top_row_base+rref+2) = c.b;			/* green */
	}	
}

