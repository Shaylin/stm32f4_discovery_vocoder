#include <math.h>
#define TWOPI 6.28318530718

void echo(uint16_t* buffer, uint32_t size);
void sineCarrier(uint16_t* buffer, uint32_t size, uint16_t freq);
void squareCarrier(uint16_t* buffer, uint32_t size, uint16_t freq);
void triCarrier(uint16_t* buffer, uint32_t size, uint16_t freq);
void distort(uint16_t* buffer, uint32_t size, float level);

void echo(uint16_t* buffer, uint32_t size)
{
	uint32_t i;
	for(i=1000; i<size; i++)
	{
		buffer[i] = buffer[i]/2 +buffer[i-1000]/2;
	}
	//Need to put this when the effects chain ends to playback
	initAudioOut(buffer,size);
	initAudioOut(buffer,size);
}

void distort(uint16_t* buffer, uint32_t size, float level)
{
	uint32_t i;
	for(i=0; i<size; i++)
	{
		//buffer[i] = (uint16_t)(buffer[i]/2.0 + rand(1000)/0.1) ;
	}
	initAudioOut(buffer,size);
	initAudioOut(buffer,size);
}

void sineCarrier(uint16_t* buffer, uint32_t size, uint16_t freq)
{
	uint32_t i;
	for(i=0; i<size; i++)
	{
		buffer[i] = (uint16_t)((buffer[i]*(sinf(TWOPI*i/16000.0*freq)+1.0))/2.0);
	}
	initAudioOut(buffer,size);
	initAudioOut(buffer,size);
}
