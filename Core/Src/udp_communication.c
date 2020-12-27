/* Functions for sending Array Structs over UDP */

#include "user_variables.h"
#include "udp_communication.h"
#include "main.h"
#include "FreeRTOS.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP.h"
#include "queue.h"
#include "arm_math.h"
#include "helper_functions.h"

static samples_input_struct *receivedStructPtr;
static float32_t fftInputData[TOTAL_SAMPLE_SIZE];
static float32_t fftResults[FFT_SIZE];


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
			/* transform message array with SAMPLE_ARRAY_SIZE to array with size of (SAMPLE_ARRAY_SIZE * EPOCHES) */
			for (unsigned int sampleCounter = 0; sampleCounter < SAMPLE_ARRAY_SIZE; sampleCounter++ )
			{
				if (receivedPackets[receivedStructPtr->messageCounter] == 0)
				{
					fftInputData[sampleCounter + receivedStructPtr->messageCounter * SAMPLE_ARRAY_SIZE] = receivedStructPtr->samples[sampleCounter];
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
				/* Toggle LED for visualization */
				HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
				/* Put Received Data into the input_samples Queue */
				xQueueSend( receivedQueue,
						    ( void * ) &fftInputData,
							0 );
				/* reset bool array */
				resetBoolArray( receivedPackets );
				#if DEBUG_MODE
					debugPrintln("Data received");
				#endif
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
		int waitingMessages = uxQueueMessagesWaiting(sendQueue);
//		UBaseType_t waitingMessages = uxQueueMessagesWaiting(sendQueue);
		if (waitingMessages > 0)
		{
			/* iterate over sendQueue */
			for (int i = 0; i < waitingMessages; i++)
			{
				/* get the next message from sendQueue */
				if (xQueueReceive( sendQueue,
					&fftResults,
					0 ) == pdPASS )
				{
					/* toggle USER_LED 2 for visualization */
					HAL_GPIO_TogglePin(LD_USER2_GPIO_Port, LD_USER2_Pin);
					/* assign packet number */
					for (unsigned int packetCounter = 0; packetCounter < (FFT_SIZE / SAMPLE_ARRAY_SIZE); packetCounter++)
					{
						samples_output_struct outputDataStructPtr;
						outputDataStructPtr.messageCounter = (double) packetCounter;
						for(unsigned int sampleCounter = 0; sampleCounter < SAMPLE_ARRAY_SIZE; sampleCounter++)
						{
							outputDataStructPtr.results[sampleCounter] = fftResults[sampleCounter + packetCounter * SAMPLE_ARRAY_SIZE];
						}
						/* send outputData over UDP */
						FreeRTOS_sendto( xSocket,
										 &outputDataStructPtr,
										 sizeof ( samples_output_struct ),
										 0,
										 &xDestinationAddress,
										 sizeof( xDestinationAddress ) );
					}
					#if DEBUG_MODE
						debugPrintln("Data send");
					#endif
				}
			}
		}
	}
}
