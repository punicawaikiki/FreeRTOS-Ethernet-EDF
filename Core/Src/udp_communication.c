/* Functions for sending Array Structs over UDP */

#include "user_variables.h"
#include "udp_communication.h"
#include "main.h"
#include "FreeRTOS.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP.h"
#include "queue.h"
#include "arm_math.h"


static samples_input_struct *receivedStructPtr;
static fft_input_samples* combinedSamplesStructPtr;
static fft_output_samples* resultsToSendStruct;
static samples_output_struct outputDataPtr;
//static samples_output_struct outputData;

unsigned char checkBoolArrayTrue ( unsigned char* receivedPackets )
{
	unsigned int count = 0;
	for (int entry = 0; entry < EPOCHES; entry++)
	{
		if (receivedPackets[entry])
		{
			count++;
		}
	}
	if (count == EPOCHES)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void resetBoolArray ( unsigned char* receivedPackets )
{
	for (int entry = 0; entry < EPOCHES; entry++)
	{
		receivedPackets[entry] = 0;
	}
}


void udpReceivingTask( void *pvParameters )
{
	int32_t lBytes;
	struct freertos_sockaddr xClient, xBindAddress;
	uint32_t xClientLength = sizeof( xClient );
	Socket_t xListeningSocket;
	unsigned char receivedPackets[EPOCHES] = {0};
	/* declare receivedQueue */
	extern QueueHandle_t receivedQueue;

   /* Attempt to open the socket. */
   xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
									   FREERTOS_SOCK_DGRAM, /*FREERTOS_SOCK_DGRAM for UDP.*/
									   FREERTOS_IPPROTO_UDP );

   /* Check the socket was created. */
   configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

   /* Bind to port 55556. */
   xBindAddress.sin_port = FreeRTOS_htons( 55556 );
   FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );

   for( ;; )
   {
	   // Receive UDP Packet
       lBytes = FreeRTOS_recvfrom( xListeningSocket,
                                   &receivedStructPtr,
                                   0,
                                   FREERTOS_ZERO_COPY,
                                   &xClient,
                                   &xClientLength );

	   if( lBytes > 0 )
	   {
			/* Data was received and can be processed here. */
			/* Toggle LED for visualization */
			HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
			/* transform message array with SAMPLE_ARRAY_SIZE to array with size of (SAMPLE_ARRAY_SIZE * EPOCHES) */
			for (unsigned int sampleCounter = 0; sampleCounter < SAMPLE_ARRAY_SIZE; sampleCounter++ )
			{
				if (receivedPackets[receivedStructPtr->messageCounter] == 0)
				{
					combinedSamplesStructPtr->y[sampleCounter + receivedStructPtr->messageCounter * SAMPLE_ARRAY_SIZE] = receivedStructPtr->y[sampleCounter];
				}
				else
				{
					break;
				}
			}
			receivedPackets[receivedStructPtr->messageCounter] = 1;
			/* check for fftInputData is filled with (SAMPLE_ARRAY_SIZE * EPOCHES) of data */
			if ( checkBoolArrayTrue( receivedPackets) )
			{
				/* Put Received Data into the input_samples Queue */
				xQueueSend( receivedQueue,
						    ( void * ) &combinedSamplesStructPtr,
							( TickType_t ) 0 );
				/* reset bool array */
				resetBoolArray( receivedPackets );
			}
	   }
       if( lBytes >= 0 )
       {
           /* The receive was successful so this RTOS task is now responsible for
           the buffer.  The buffer must be freed once it is no longer
           needed. */

           /*
            * The data can be processed here.
            */

           /* Return the buffer to the TCP/IP stack. */
           FreeRTOS_ReleaseUDPPayloadBuffer( receivedStructPtr );
       }
   }
}

/* Sending data from sendQueue over UDP to Computer */
void udpSendingTask( void *pvParameters )
{
	Socket_t xSocket;
	struct freertos_sockaddr xDestinationAddress;
	/* declare sendQueue */
	extern QueueHandle_t sendQueue;

	/* Send strings to port 55555 on IP address 192.168.1.1. */
	xDestinationAddress.sin_addr = FreeRTOS_inet_addr( "192.168.1.1" );
	xDestinationAddress.sin_port = FreeRTOS_htons( 55555 );

	/* Create the socket. */
	xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
							  FREERTOS_SOCK_DGRAM,/*FREERTOS_SOCK_DGRAM for UDP.*/
							  FREERTOS_IPPROTO_UDP );

	/* Check the socket was created. */
	configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

	for( ;; )
	{
		/* get number of messages in sendQueue */
		UBaseType_t waitingMessages = uxQueueMessagesWaiting(sendQueue);
		if (waitingMessages > 0)
		{
			/* iterate over sendQueue */
			for (int i = 0; i < waitingMessages; i++)
			{
				/* toggle USER_LED 2 for visualization */
				HAL_GPIO_TogglePin(LD_USER2_GPIO_Port, LD_USER2_Pin);
				/* get the next message from sendQueue */
				xQueueReceive( sendQueue,
							   &resultsToSendStruct,
							   ( TickType_t ) 0 );
				/* assign packet number */
				for (unsigned int packetCounter = 0; packetCounter < (FFT_SIZE / SAMPLE_ARRAY_SIZE); packetCounter++)
				{
					outputDataPtr.messageCounter = packetCounter;
					for(unsigned int sampleCounter = 0; sampleCounter < SAMPLE_ARRAY_SIZE; sampleCounter++)
					{
						outputDataPtr.results[sampleCounter] = resultsToSendStruct->y[sampleCounter + packetCounter * SAMPLE_ARRAY_SIZE];
					}
					/* send outputData over UDP */
					FreeRTOS_sendto( xSocket,
									 &outputDataPtr,
									 sizeof ( samples_output_struct ),
									 0,
									 &xDestinationAddress,
									 sizeof( xDestinationAddress ) );
				}
			}
		}
	}
}
