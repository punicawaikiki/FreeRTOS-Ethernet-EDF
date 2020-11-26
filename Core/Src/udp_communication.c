/* Functions for sending Array Structs over UDP */

#include "udp_communication.h"
#include "main.h"
#include "FreeRTOS.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP.h"
#include "queue.h"
#include "user_structs.h"


QueueHandle_t receivedQueue = NULL;
static samples_struct receivedStruct;

void udpReceivingTask( void *pvParameters )
{
	int32_t lBytes;
	struct freertos_sockaddr xClient, xBindAddress;
	uint32_t xClientLength = sizeof( xClient );
	Socket_t xListeningSocket;

	receivedQueue = xQueueCreate( 32, sizeof(samples_struct * ));

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
								   &receivedStruct,
								   sizeof( receivedStruct ),
								   0,
								   &xClient,
								   &xClientLength );

	   if( lBytes > 0 )
	   {
		   /* Data was received and can be processed here. */
		   /* Toggle LED for visual signaling */
		   HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
		   /* Put Received Data into the input_samples Queue */
		   xQueueSend( receivedQueue, &receivedStruct, ( TickType_t ) 0);
	   }
   }
}

void udpSendingTask( void *pvParameters )
{
	Socket_t xSocket;
	struct freertos_sockaddr xDestinationAddress;

	const TickType_t x1000ms = 1000UL / portTICK_PERIOD_MS;

   /* Send strings to port 55555 on IP address 192.168.1.1. */
   xDestinationAddress.sin_addr = FreeRTOS_inet_addr( "192.168.1.1" );
   xDestinationAddress.sin_port = FreeRTOS_htons( 55555 );
   single_sample_struct sendStruct;
   sendStruct.x = 1.1;
   sendStruct.y = 2.12345;


   /* Create the socket. */
   xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                              FREERTOS_SOCK_DGRAM,/*FREERTOS_SOCK_DGRAM for UDP.*/
                              FREERTOS_IPPROTO_UDP );

   /* Check the socket was created. */
   configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

   /* NOTE: FreeRTOS_bind() is not called.  This will only work if
   ipconfigALLOW_SOCKET_SEND_WITHOUT_BIND is set to 1 in FreeRTOSIPConfig.h. */
   for( ;; )
   {
	   HAL_GPIO_TogglePin(LD_USER2_GPIO_Port, LD_USER2_Pin);
       FreeRTOS_sendto( xSocket,
                        &sendStruct,
                        sizeof( sendStruct ),
                        0,
                        &xDestinationAddress,
                        sizeof( xDestinationAddress ) );
       /* Wait until it is time to send again. */
       vTaskDelay( x1000ms );
   }
}
