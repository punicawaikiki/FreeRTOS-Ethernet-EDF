/* FFT Task and helper functions */


#include <user_variables.h>
#include "arm_math.h"
#include "FreeRTOS.h"
#include "queue.h"


/* define globals */
static fft_input_samples* fftInputStructPtr;
//static fft_output_samples *resultsStructPtr;
static float32_t fftInputData[TOTAL_SAMPLE_SIZE];
static float32_t fftOutputData[FFT_SIZE * 4];
static float32_t fftOutputDataMag[FFT_SIZE];
static float32_t fftShiftOutputData[TOTAL_SAMPLE_SIZE];


/* Task for receiving data from receivedQueue, calculate fft, calculate magnitude and push results to sendQueue */
void calculateFFT( void *pvParameters )
{
	/* declare Queue`s */
	extern QueueHandle_t receivedQueue;
	extern QueueHandle_t sendQueue;
	/* Create FFT Instances */
	arm_rfft_instance_q15 RealFFT_Instance;
	/* Initialize the FFT Structures	 */
	arm_rfft_init_q15(&RealFFT_Instance,
					  FFT_SIZE,
					  0,
					  1); //Normal Order
    for( ;; )
    {
    	/* get number of messages in receivedQueue */
    	UBaseType_t waitingMessages = uxQueueMessagesWaiting(receivedQueue);
    	if (waitingMessages > 0)
    	{
        	fft_output_samples* resultsStructPtr = NULL;
        	resultsStructPtr = pvPortMalloc( sizeof( fft_output_samples ) );
        	if ( resultsStructPtr != NULL)
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
        				arm_rfft_q15(&RealFFT_Instance,
        							 (q15_t *) fftInputData,
        							 (q15_t *) fftOutputData);
        //				arm_shift_q15( (q15_t *) fftOutputData,
        //							   8,
        //							   (q15_t *) fftShiftOutputData,
        //							   FFT_SIZE
        //							   );
        				/* Process the data through the Complex Magnitude Module for
        				  calculating the magnitude at each bin */
        				arm_cmplx_mag_q15((q15_t *) fftOutputData,
        								  (q15_t *) fftOutputDataMag,
        								  TOTAL_SAMPLE_SIZE);
        				for (int i = 0; i < FFT_SIZE; i++)
        				{
        					resultsStructPtr->y[i] = fftOutputDataMag[i];
        				}

        				/* put queueSendData into sendQueue */
        				xQueueSend( sendQueue,
        							( void * ) &resultsStructPtr,
        							( TickType_t ) 0 );
        				vPortFree(resultsStructPtr);
            		}
        		}
        	}
        	else
        	{
        		int i = 0;
        	}
    	}

    }
}
