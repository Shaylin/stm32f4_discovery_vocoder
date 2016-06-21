/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "audio_out.h"
#include "audio_in.h"
#include "audio_process.h"
#include "buttons.h"
#include <stdlib.h>

uint8_t inputDone = 1;
uint8_t outputDone = 1;
uint8_t processDone = 0;
uint16_t* buffer;
uint32_t size = 64000;

void DMA2_Stream0_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
	{
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
		inputDone = 1;
		echo(buffer,size);
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5))
	{
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
		outputDone = 1;
	}
}

int main(void)
{
	buffer = (uint16_t*)malloc(sizeof(uint16_t)*size);
	initButtons();

	while (1)
	{
		if(inputDone)
		{
			STM_EVAL_LEDInit(LED4);
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOff(LED5);
		}
		else
		{
			STM_EVAL_LEDOff(LED4);
			STM_EVAL_LEDInit(LED5);
			STM_EVAL_LEDOn(LED5);
		}
		if(outputDone && checkButton(0)==1)
		{
			inputDone = 0;
			outputDone = 0;
			initAudioIn(buffer, size);
		}

		if(checkButton(0)==1)
		{
			STM_EVAL_LEDInit(LED3);
			STM_EVAL_LEDOn(LED3);
		}
		else
		{
			STM_EVAL_LEDOff(LED3);
		}
	}
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){return;}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){return -1;}
