/* This File includes all defined hooks */

#include "hooks.h"
#include "udp_communication.h"
#include "main.h"
#include "fft.h"
#include "helper_functions.h"
#include "edf_tasks.h"
#include "strings.h"


#if DEBUG_MODE
	extern edfTasks_s edfTasks;
#endif


/* Declaration of tasks pointers */
TaskHandle_t* UDPReceiveTaskHandle = NULL;
TaskHandle_t* UDPSendTaskHandle = NULL;
TaskHandle_t* FFTTaskHandle = NULL;


const char *pcApplicationHostnameHook( void )
{
	/* Assign the name "rtosdemo" to this network node.  This function will be
	called during the DHCP: the machine will be registered with an IP address
	plus this name. */
	return mainHOST_NAME;
}


BaseType_t xApplicationDNSQueryHook( const char *pcName )
{
BaseType_t xReturn;

	/* Determine if a name lookup is for this node.  Two names are given
	to this node: that returned by pcApplicationHostnameHook() and that set
	by mainDEVICE_NICK_NAME. */
	if( strcasecmp( pcName, pcApplicationHostnameHook() ) == 0 )
	{
		xReturn = pdPASS;
	}
	else if( strcasecmp( pcName, mainDEVICE_NICK_NAME ) == 0 )
	{
		xReturn = pdPASS;
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}


void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
static BaseType_t xTasksAlreadyCreated = pdFALSE;
    /* Both eNetworkUp and eNetworkDown events can be processed here. */
    if( eNetworkEvent == eNetworkUp )
    {
		#if DEBUG_MODE
    		debugPrintln("Network is up, create Tasks");
		#endif
		createEDFTask(udpReceivingTask, "UDPReceive", (unsigned short ) 200, NULL, 2, 10, 10); // create Receiving task (wcet 2ms, period 10ms, deadline 10ms)
		createEDFTask(calculateFFT, "FFT", (unsigned short ) 200, NULL, 2, 10, 10); // create FFT task (wcet 2ms, period 10ms, deadline 10ms)
		createEDFTask(udpSendingTask, "UDPSend", (unsigned short ) 400, NULL, 2, 10, 10); // create Sending task (wcet 2ms, period 10ms, deadline 10ms)
        /* Create the tasks that use the TCP/IP stack if they have not already
        been created. */
        if( xTasksAlreadyCreated == pdFALSE )
        {
            /*
             * For convenience, tasks that use FreeRTOS+TCP can be created here
             * to ensure they are not created before the network is usable.
             */

            xTasksAlreadyCreated = pdTRUE;
        }
    }
    else
    {
		#if DEBUG_MODE == 1
    		debugPrintln("Network is down, waiting ...");
		#endif
    }
}


void vApplicationMallocFailedHook(void)
{
    /* The malloc failed hook is enabled by setting
    configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.
    Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	debugPrintln("Malloc Failed Hook called!!!");
    for( ;; );
}


void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) xTask;

    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  pxCurrentTCB can be
    inspected in the debugger if the task name passed into this function is
    corrupt. */
    for( ;; )
    {
		/* Toggle LED for visualization */
		HAL_GPIO_TogglePin(LD_USER2_GPIO_Port, LD_USER2_Pin);
    }
}

