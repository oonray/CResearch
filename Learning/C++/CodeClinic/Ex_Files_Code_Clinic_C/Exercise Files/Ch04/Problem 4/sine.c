/*
   sine
   Written by Dan Gookin
   Based on sample code provided for the PortAudio library: http://portaudio.com/

   Generate a sine wave table and play the table.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "portaudio.h"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER (64)
#define TABLE_SIZE (307)

#ifndef M_PI
#define M_PI (3.14159625)
#endif

typedef struct
{
	float sine[TABLE_SIZE];
	int left_phase;
	int right_phase;
	char message[20];
}
paTestData;

int beep(int duration);
int error_terminate(PaError err);
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData );
static void StreamFinished(void *userData);

int main()
{
	beep(100);
	return(0);
}

/*
	diration - play milliseconds, 100 = one second
	TABLE_SIZE is the frequency, the audio pitch
*/
int beep(int duration)
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	paTestData data;
	int i;
	
	/* initialize wave table */
	for(i=0;i<TABLE_SIZE;i++)
	{
			/* 4.0 makes a smoother wave */
		data.sine[i] = (float)sin(((double)i/(double)TABLE_SIZE) * M_PI * 4.0);
	}

	data.left_phase = data.right_phase = 0;

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
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	
	err = Pa_OpenStream(
				&stream,
				NULL,          				/* no input channels on output-only stream */
				&outputParameters,          /* stereo output */
				SAMPLE_RATE,
				FRAMES_PER_BUFFER,
				paClipOff,
				patestCallback,
				&data );
	if( err != paNoError ) error_terminate(err);

	sprintf(data.message,"No Message");
	err = Pa_SetStreamFinishedCallback(stream,&StreamFinished);
	if( err != paNoError ) error_terminate(err);
	 
	err = Pa_StartStream( stream );
	if( err != paNoError ) error_terminate(err);

	printf("Play for %d milliseconds.\n",duration);
	Pa_Sleep(duration*10);

	err = Pa_StopStream( stream );
	if( err != paNoError ) error_terminate(err);

	err = Pa_CloseStream( stream );
	if( err != paNoError ) error_terminate(err);

	Pa_Terminate();
	printf("Test finished.\n");
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

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned long i;
	
	(void)timeInfo;		/* Prevent unused variable warning. */
	(void)statusFlags;
	(void)inputBuffer;

	for( i=0; i<framesPerBuffer; i++ )
	{
		*out++ = data->sine[data->left_phase];  /* left */
		*out++ = data->sine[data->right_phase];  /* right */
		data->left_phase += 1;
		if( data->left_phase >= TABLE_SIZE ) data->left_phase -= TABLE_SIZE;
		data->right_phase += 1;
		if( data->right_phase >= TABLE_SIZE ) data->right_phase -= TABLE_SIZE;
	}
	return paContinue;
}

static void StreamFinished(void *userData)
{
	paTestData *data = (paTestData *)userData;
	printf("Stream completed: %s\n",data->message);
}
