/* FFT Task and helper functions */


#include "arm_math.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "user_structs.h"

/* define globals */
#define EPOCHES 16
static samples_struct samples_array[EPOCHES];

void calculateFFT( void *pvParameters )
{
	uint32_t messageCounter = 0;
	extern QueueHandle_t receivedQueue;
	samples_struct receivedStruct;
	/* Create FFT Instances */
	arm_rfft_instance_q15 RealFFT_Instance;
	arm_cfft_radix4_instance_q15 MyComplexFFT_Instance;
	/* Initialize the FFT Structures	 */
	arm_rfft_init_q15(&RealFFT_Instance,
					  128,
					  0,
					  1); //Normal Order
//	samples_struct* samples_array;
//	 = (samples_struct*) pvPortMalloc(epoches * sizeof(samples_struct));

//	arm_status status;
//	float32_t maxValue;
//	status = ARM_MATH_SUCCESS;
//	status=arm_cfft_init_f32(&varInstCfftF32,fftSize);
//	/* Process the data through the CFFT/CIFFT module */
//	arm_cfft_f32(&varInstCfftF32, testInput_f32_10khz, ifftFlag, doBitReverse);
//	/* Process the data through the Complex Magnitude Module for
//	calculating the magnitude at each bin */
//	arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);
//	/* Calculates maxValue and returns corresponding BIN value */
//	arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
//	status = (testIndex != refIndex) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

    for( ;; )
    {
    	UBaseType_t waitingMessages = uxQueueMessagesWaiting(receivedQueue);
    	if (waitingMessages > 0)
    	{
    		for (int i = 0; i < waitingMessages; i++)
    		{
        		xQueueReceive( receivedQueue, &receivedStruct, ( TickType_t ) 0);
        		samples_array[messageCounter] = receivedStruct;
        		messageCounter++;
    		}
        	if (messageCounter == EPOCHES -1)
        	{
        		// TODO: Implement FFT here
        		arm_rfft_q15(&RealFFT_Instance,
        				     (q15_t *) receivedBuffer,
							 /(q15_t *) fftOutput);
        		messageCounter = 0;
        	}
}

    }
}


//void calculateFFT( void *pvParameters )
//{
//	int epoches = 100;
//	const TickType_t x1000ms = 1000UL / portTICK_PERIOD_MS;
//	extern QueueHandle_t receivedQueue;
//	samples_struct receivedStruct;
//	samples_struct samples_array[epoches];
//	uint32_t messageCounter = 0;
//
////	arm_status status;
////	float32_t maxValue;
////	status = ARM_MATH_SUCCESS;
////	status=arm_cfft_init_f32(&varInstCfftF32,fftSize);
////	/* Process the data through the CFFT/CIFFT module */
////	arm_cfft_f32(&varInstCfftF32, testInput_f32_10khz, ifftFlag, doBitReverse);
////	/* Process the data through the Complex Magnitude Module for
////	calculating the magnitude at each bin */
////	arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);
////	/* Calculates maxValue and returns corresponding BIN value */
////	arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
////	status = (testIndex != refIndex) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;
//
//    for( ;; )
//    {
////    	UBaseType_t waitingMessages = uxQueueMessagesWaiting(receivedQueue);
////    	if (waitingMessages > 0)
//    	if (1)
//    	{
//        	xQueueReceive( receivedQueue, &receivedStruct, ( TickType_t ) 0);
////        	samples_array[messageCounter] = &receivedStruct;
//        	messageCounter++;
//
//    	}
//    	if ( epoches == messageCounter - 1)
//    	{
//    		int i = 0;
//    	}
//    	vTaskDelay(x1000ms);
//    }
//}
