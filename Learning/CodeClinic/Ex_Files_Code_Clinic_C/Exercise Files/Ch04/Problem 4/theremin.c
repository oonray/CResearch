/*
	theremin
	Written by Dan Gookin, February 21, 2015
	
	This code uses the NCurses and PortAudio libraries.
	
	http://invisible-island.net/ncurses/
	http://portaudio.com/

	NCurses controls the display, but also reads the mouse. PortAudio
	generates tones. Lamentably, volume cannot be controlled.
*/

/* REQUIRED PORT AUDIO COPYRIGHT NOTICE
 * $Id: paex_write_sine.c 1865 2012-09-01 21:16:25Z philburk $
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com/
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <portaudio.h>
#include <string.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 1024
#define PI 3.14159625

int tone(float duration,int frequency,float volume);
int error_terminate(PaError err);

int main(int argc, char *argv[])
{
	MEVENT mort;
	int rows,cols,ch,x,y;
	int frequency_increment;
	
	/* process command line argument before starting NCurses */
	if( argc==2 && strcmp(argv[1],"--help") == 0)
	{
		puts("theremin\nWritten by Dan Gookin, 2015\n");
		puts("Reads mouse position on the terminal screen and generates tones.");
		puts("Up-down sets pitch; left-right sets volume.");
		return(1);
	}

	/* initialize NCurses */
	initscr();
	start_color();
	noecho();
	keypad(stdscr,TRUE);

	/* Calculate frequency  range based on screen size */
	getmaxyx(stdscr,rows,cols);
	frequency_increment = 200/rows;
	
	/* configure screen colors and mouse */
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_RED);
	init_pair(3,COLOR_BLUE,COLOR_BLUE);
	mousemask(ALL_MOUSE_EVENTS,NULL);
	mvaddstr(0,4,"Press Enter to end:");
	refresh();

	/* loop forever until the Enter key is pressed */
	while(1)
	{
		ch = getch();
		if( ch == KEY_MOUSE )
		{
			clear();
			attrset(COLOR_PAIR(1));
			mvaddstr(0,4,"Press Enter to end:");
			getmouse(&mort);
			tone(0.5,mort.y*frequency_increment+120,(float)mort.x/cols*0.5);
			/* Plot Volume left-right */
			attrset(COLOR_PAIR(2));
			for(x=0;x<mort.x;x++)
				mvaddch(LINES-1,x,'X');
			/* Plot Frequency top-down */
			attrset(COLOR_PAIR(3));
			for(y=mort.y;y<LINES-1;y++)
				mvaddstr(y,0,"XXX");
			/* update the display */
			refresh();
			continue;
		}
		if( ch == '\n' )
			break;
	}

	endwin();
	return 0;
}

/*
	This function uses and modifies the code for paex_write_sine.c:
	
	http://portaudio.com/docs/v19-doxydocs/paex__write__sine_8c_source.html

	I've added options for duration (in seconds) and frequency. I also removed
	the ugly goto commands. Frequency is achieved by resizing the sine buffer,
	which compresses the wave and generates a different tone.
	
	This is a non-interruptible routine, so it cannot be interactive. The
	PortAudio library is primarily designed to record and play back chunks
	of audio, not to generate tones.
*/
int tone(float duration,int frequency,float volume)
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	float buffer[FRAMES_PER_BUFFER][2];	/* stereo output buffer */
	float sine[frequency];	/* sine wavetable */
	int left_phase  = 0;
	int right_phase = 0;
	int i,j,bufferCount;
	
	/* initialize wave table */
	for(i=0;i<frequency;i++)
	{
		sine[i] = (float)sin(((double)i/(double)frequency) * PI * volume);
	}

	/* Start Port Audio */
	err = Pa_Initialize();
	if( err != paNoError ) error_terminate(err);

	/* fill the stream structure */
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if(outputParameters.device == paNoDevice)
	{
		fprintf(stderr,"Error: No default output device.\n");
		error_terminate(err);
	}
	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = 0.050;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	/* Open the output stream */
	err = Pa_OpenStream(
				&stream,
				NULL,
				&outputParameters,
				SAMPLE_RATE,
				FRAMES_PER_BUFFER,
				paClipOff,
				NULL,
				NULL );
	if( err != paNoError ) error_terminate(err);

	/* start the stream and configure the output buffer */
	err = Pa_StartStream(stream);
	if( err != paNoError ) error_terminate(err);
		
	bufferCount = ((duration * (float)SAMPLE_RATE) / (float)FRAMES_PER_BUFFER);
	for(i=0;i<bufferCount;i++)
	{
		for(j=0;j<FRAMES_PER_BUFFER;j++)
		{
			buffer[j][0] = sine[left_phase];
			buffer[j][1] = sine[right_phase];
			left_phase += 1;
			if( left_phase >= frequency)
				left_phase -= frequency;
			right_phase += 1;
			if( right_phase >= frequency)
				right_phase -= frequency;
		}
		/* output the sound */
		err = Pa_WriteStream(stream,buffer,FRAMES_PER_BUFFER);
		if( err != paNoError) error_terminate(err);
	}
	/* stop the stream */
	err = Pa_StopStream(stream);
	if( err != paNoError) error_terminate(err);

	/* close the stream */
	err = Pa_CloseStream(stream);
	if( err != paNoError ) error_terminate(err);

	/* shut down Port Audio */
	Pa_Terminate();

	return err;
}

/*
	PortAudio error handler.
*/
int error_terminate(PaError err)
{
	Pa_Terminate();
	endwin();			/* must terminate NCurses */
	fprintf( stderr, "An error occured while using the portaudio stream\n" );
	fprintf( stderr, "Error number: %d\n", err );
	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
	exit(1);
}

