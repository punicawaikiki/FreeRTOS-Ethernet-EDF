/* FFT Task and helper functions */


#include <user_variables.h>
#include "arm_math.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "main.h"
#include "helper_functions.h"


/* define globals */
static fft_input_samples* fftInputStructPtr;
static float32_t fftInputData[TOTAL_SAMPLE_SIZE];
static float32_t fftOutputData[TOTAL_SAMPLE_SIZE];
static float32_t fftOutputDataMag[FFT_SIZE];

/* Task for receiving data from receivedQueue, calculate fft, calculate magnitude and push results to sendQueue */
void calculateFFT( void *pvParameters )
{
	/* declare Queue`s */
	extern QueueHandle_t receivedQueue;
	extern QueueHandle_t sendQueue;
	/* Create FFT Instances */
	arm_rfft_fast_instance_f32 S;
	arm_status status;
	/* Initialize the FFT Structures	 */
	status = arm_rfft_fast_init_f32(&S, TOTAL_SAMPLE_SIZE);
	if ( status != ARM_MATH_SUCCESS )
	{
		HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
	}
    for( ;; )
    {
    	/* get number of messages in receivedQueue */
    	UBaseType_t waitingMessages = uxQueueMessagesWaiting(receivedQueue);
    	if (waitingMessages > 0)
    	{
			/* iterate over number of messages in receivedQueue */
			for (int i = 0; i < waitingMessages; i++)
			{
				/* get one message from receivedQueue */
				if (xQueueReceive( receivedQueue,
							   &fftInputStructPtr,
							   ( TickType_t ) 10 ) == pdPASS )
				{
					for (int i = 0; i < TOTAL_SAMPLE_SIZE; i++)
					{
						fftInputData[i] = fftInputStructPtr->y[i];
					}
					/* calculate fft */
					arm_rfft_fast_f32(&S, fftInputData, fftOutputData, 0);
					/* Process the data through the Complex Magnitude Module for
					  calculating the magnitude at each bin */
					arm_cmplx_mag_f32( fftOutputData, fftOutputDataMag, FFT_SIZE);
					xQueueSend( sendQueue,
								( void * ) &(fftOutputDataMag),
								( TickType_t ) 0 );
				}
        	}
    	}
    }
}
