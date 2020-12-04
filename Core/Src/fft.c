/* FFT Task and helper functions */


#include <user_variables.h>
#include "arm_math.h"
#include "FreeRTOS.h"
#include "queue.h"

/* define globals */
static float32_t fftInputData[SAMPLE_ARRAY_SIZE * EPOCHES];
static float32_t fftOutputData[(SAMPLE_ARRAY_SIZE * EPOCHES) / 2];
static float32_t fftOutputDataMag[(SAMPLE_ARRAY_SIZE * EPOCHES) / 2];
static test_struct *queueSendData;
static samples_struct *bufferStruct;


/* Task for receiving data from receivedQueue, calculate fft, calculate magnitude and push results to sendQueue */
void calculateFFT( void *pvParameters )
{
	uint32_t messageCounter = 0;
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
    		/* iterate over number of messages in receivedQueue */
    		for (int i = 0; i < waitingMessages; i++)
    		{
    			/* get one message from receivedQueue */
        		xQueueReceive( receivedQueue,
        					   &bufferStruct,
							   ( TickType_t ) 0 );
        		/* transform message array with SAMPLE_ARRAY_SIZE to array with size of (SAMPLE_ARRAY_SIZE * EPOCHES) */
        		for (int i = 0; i < SAMPLE_ARRAY_SIZE; i++)
        		{
        			fftInputData[i + messageCounter * SAMPLE_ARRAY_SIZE] = bufferStruct->y[i];
        		}
        		/* check for fftInputData is filled with (SAMPLE_ARRAY_SIZE * EPOCHES) of data */
            	if (messageCounter < EPOCHES )
            	{
            		/* calculate fft */
            		arm_rfft_q15(&RealFFT_Instance,
            				     (q15_t *) fftInputData,
    							 (q15_t *) fftOutputData);
            		/* Process the data through the Complex Magnitude Module for
            		  calculating the magnitude at each bin */
            		arm_cmplx_mag_q15((q15_t *) fftOutputData,
            						  (q15_t *) fftOutputDataMag,
									  EPOCHES * SAMPLE_ARRAY_SIZE);
            		unsigned int fftOuputDataMagCounter = 0;
            		/* Split results in pieces of SAMPLE_ARRAY_SIZE and put it into sendQueue */
            		for ( unsigned int epochesCounter = 0; epochesCounter < (EPOCHES / 2); epochesCounter++)
            		{
            			for ( unsigned int sampleSizeCounter = 0; sampleSizeCounter < SAMPLE_ARRAY_SIZE ; sampleSizeCounter++)
            			{
            				/* copy SAMPLE_SIZE_ARRAY of data into queueSendData array */
            				queueSendData->results[sampleSizeCounter] = (double) (fftOutputDataMag[fftOuputDataMagCounter]);
            				fftOuputDataMagCounter++;
            			}
            			/* put queueSendData into sendQueue */
                		xQueueSend( sendQueue,
                				    &queueSendData,
    								( TickType_t ) 0 );
            		}
            		messageCounter = 0;
    			}
        		messageCounter++;
    		}
    	}

    }
}
