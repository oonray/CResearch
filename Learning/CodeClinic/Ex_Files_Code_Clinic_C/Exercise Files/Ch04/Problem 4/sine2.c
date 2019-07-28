/*
   sine2
   Written by Dan Gookin
   Based on sample code provided for the PortAudio library: http://portaudio.com/

   Experiment with generating certain tones by rebuilding the wave table.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "portaudio.h"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER (1024)

#ifndef M_PI
#define M_PI (3.14159625)
#endif

int beep(float duration,int volume,int frequency);
int error_terminate(PaError err);

int main()
{
	int x;

	for(x=170;x<250;x+=10)
	{
		beep(1.0,1,x);
	}
	
	return(0);
}

/*
	duration = time in seconds
	volume, 1 = medium, 2 = loud
	Frequency: 170/G, 180/B, 190/G, 200/G, 210/G, 220/G, 230/G, 240/G, 250/, 260/, 270/A
*/
int beep(float duration,int volume,int frequency)
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	float buffer[FRAMES_PER_BUFFER][2];	/* stereo output buffer */
	float sine[frequency];	/* sine wavetable */
	int left_phase  = 0;
	int right_phase = 0;
	int i,j,bufferCount;
	
	printf("Frequency %d\n",frequency);
	
	/* initialize wave table */
	for(i=0;i<frequency;i++)
	{
		sine[i] = (float)sin(((double)i/(double)frequency) * M_PI * 4.0);
	}

	err = Pa_Initialize();
	if( err != paNoError ) error_terminate(err);

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

	err = Pa_OpenStream(
				&stream,
				NULL,          				/* no input channels on output-only stream */
				&outputParameters,          /* stereo output */
				SAMPLE_RATE,
				FRAMES_PER_BUFFER,
				paClipOff,
				NULL,
				NULL );
	if( err != paNoError ) error_terminate(err);

	err = Pa_StartStream(stream);
	if( err != paNoError ) error_terminate(err);
		
	bufferCount = ((duration * (float)SAMPLE_RATE) / (float)FRAMES_PER_BUFFER);
		
	for(i=0;i<bufferCount;i++)
	{
		for(j=0;j<FRAMES_PER_BUFFER;j++)
		{
			buffer[j][0] = sine[left_phase];
			buffer[j][1] = sine[right_phase];
			left_phase += volume;
			if( left_phase >= frequency)
				left_phase -= frequency;
			right_phase += volume;
			if( right_phase >= frequency)
				right_phase -= frequency;
		}
		err = Pa_WriteStream(stream,buffer,FRAMES_PER_BUFFER);
		if( err != paNoError) error_terminate(err);
	}
	err = Pa_StopStream(stream);
	if( err != paNoError) error_terminate(err);

	err = Pa_CloseStream(stream);
	if( err != paNoError ) error_terminate(err);

	Pa_Terminate();

	return err;
}

int error_terminate(PaError err)
{
	Pa_Terminate();
	fprintf( stderr, "An error occured while using the portaudio stream\n" );
	fprintf( stderr, "Error number: %d\n", err );
	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
	exit(1);
}
