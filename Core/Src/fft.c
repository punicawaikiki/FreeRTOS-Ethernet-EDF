/* FFT Task and helper functions */


#include <user_variables.h>
#include "arm_math.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "main.h"


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
		HAL_GPIO_WritePin(LD_USER3_GPIO_Port, LD_USER3_Pin, 1);
	}
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
        				arm_rfft_fast_f32(&S, fftInputData, fftOutputData, 0);
//        				/* Process the data through the Complex Magnitude Module for
//        				  calculating the magnitude at each bin */
        				arm_cmplx_mag_f32( fftOutputData, fftOutputDataMag, FFT_SIZE);
        				for (int i = 0; i < FFT_SIZE; i++)
        				{
        					resultsStructPtr->y[i] = fftOutputDataMag[i];
        				}

        				/* put queueSendData into sendQueue */
        				xQueueSend( sendQueue,
        							( void * ) &resultsStructPtr,
        							( TickType_t ) 0 );
//        				vTaskDelay( 1000UL / portTICK_PERIOD_MS );
        				vPortFree(resultsStructPtr);
            		}
        		}
        	}
    	}

//    	/* get number of messages in receivedQueue */
//    	UBaseType_t waitingMessages = uxQueueMessagesWaiting(receivedQueue);
//    	if (waitingMessages > 0)
//    	{
//        	fft_output_samples* resultsStructPtr = NULL;
//        	resultsStructPtr = pvPortMalloc( sizeof( fft_output_samples ) );
//        	int test = sizeof( fft_output_samples);
//        	if ( resultsStructPtr != NULL)
//        	{
//        		/* iterate over number of messages in receivedQueue */
//        		for (int i = 0; i < waitingMessages; i++)
//        		{
//        			/* get one message from receivedQueue */
//            		if (xQueueReceive( receivedQueue,
//            					   &fftInputStructPtr,
//    							   ( TickType_t ) 10 ) == pdPASS )
//            		{
//        				for (int i = 0; i < TOTAL_SAMPLE_SIZE; i++)
//        				{
//        					fftInputData[i] = fftInputStructPtr->y[i];
//        				}
//        				/* calculate fft */
//        				arm_rfft_fast_f32(&S, fftInputData, fftOutputData, 0);
//        				arm_cmplx_mag_f32(fftOutputData, fftOutputDataMag, TOTAL_SAMPLE_SIZE);
//        //				arm_shift_q15( (q15_t *) fftOutputData,
//        //							   8,
//        //							   (q15_t *) fftShiftOutputData,
//        //							   FFT_SIZE
//        //							   );
//        				/* Process the data through the Complex Magnitude Module for
//        				  calculating the magnitude at each bin */
////        				arm_cmplx_mag_q15((q15_t *) fftOutputData,
////        								  (q15_t *) fftOutputDataMag,
////        								  TOTAL_SAMPLE_SIZE);
//        				for (int i = 0; i < FFT_SIZE; i++)
//        				{
//        					resultsStructPtr->y[i] = fftOutputDataMag[i];
//        				}
//
//        				/* put queueSendData into sendQueue */
//        				xQueueSend( sendQueue,
//        							( void * ) &resultsStructPtr,
//        							( TickType_t ) 0 );
//        				vPortFree(resultsStructPtr);
//            		}
//        		}
//        	}
//        	else
//        	{
//        		int i = 0;
//        	}
//    	}

    }
}
