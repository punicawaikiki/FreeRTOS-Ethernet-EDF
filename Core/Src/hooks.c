/* This File includes all defined hooks */

#include "hooks.h"
#include "udp_communication.h"
#include "main.h"
#include "fft.h"
#include "helper_functions.h"

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
		#if DEBUG_MODE == 1
    	debugPrintln("Network is up, create Tasks");
		#endif
    	xTaskCreate( udpReceivingTask, "UDPReceive", ( unsigned short ) 500 , NULL, 4, UDPReceiveTaskHandle );
    	xTaskCreate( calculateFFT, "FFT", ( unsigned short ) 500 , NULL, 1, FFTTaskHandle );
    	xTaskCreate( udpSendingTask, "UDPSend", ( unsigned short ) 500 , NULL, 1, UDPSendTaskHandle );
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
    	if (HAL_GPIO_ReadPin(LD_USER1_GPIO_Port, LD_USER1_Pin) != 1)
    	{
    		HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
    	}
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
    for( ;; );
}

void vApplicationIdleHook(void)
{
    /* The malloc failed hook is enabled by setting
    configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.
    Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    for( ;; );
}
