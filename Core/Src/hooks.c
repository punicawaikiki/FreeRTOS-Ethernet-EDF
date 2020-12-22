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
    	debugPrintln("Network is up, create Tasks");
//    	xTaskCreate( udpSendingTask, "UDPSend", ( unsigned short ) 500 , NULL, standardTASK_PRIORITY, UDPSendTaskHandle );
//    	xTaskCreate( udpReceivingTask, "UDPReceive", ( unsigned short ) 500 , NULL, standardTASK_PRIORITY, UDPReceiveTaskHandle );
//    	xTaskCreate( calculateFFT, "FFT", ( unsigned short ) 500 , NULL, standardTASK_PRIORITY, FFTTaskHandle );
    	xTaskCreate( udpReceivingTask, "UDPReceive", ( unsigned short ) 500 , NULL, 3, UDPReceiveTaskHandle );
    	xTaskCreate( calculateFFT, "FFT", ( unsigned short ) 500 , NULL, 2, FFTTaskHandle );
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
    	debugPrintln("Network is down, waiting ...");
    	if (HAL_GPIO_ReadPin(LD_USER1_GPIO_Port, LD_USER1_Pin) != 1)
    	{
    		HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
    	}
    }
}


void vApplicationMallocFailedHook(void)
{
	debugPrintln("Malloc Failed Hook called!!!");
}
