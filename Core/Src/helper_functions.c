/* This File includes all needed helper Functions */


#include "helper_functions.h"
#include "task.h"
#include "usart.h"
#include "string.h"
#include "user_variables.h"

void prvSRand( UBaseType_t ulSeed )
{
	/* Utility function to seed the pseudo random number generator. */
	ulNextRand = ulSeed;
}

UBaseType_t uxRand( void )
{
const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;
static BaseType_t xInitialised = pdFALSE;

	/* Don't initialise until the scheduler is running, as the timeout in the
	random number generator uses the tick count. */
	if( xInitialised == pdFALSE )
	{
		if( xTaskGetSchedulerState() !=  taskSCHEDULER_NOT_STARTED )
		{
		RNG_HandleTypeDef xRND;
		uint32_t ulSeed;

			/* Generate a random number with which to seed the local pseudo random
			number generating function. */
			HAL_RNG_Init( &xRND );
			HAL_RNG_GenerateRandomNumber( &xRND, &ulSeed );
			prvSRand( ulSeed );
			xInitialised = pdTRUE;
		}
	}

	/* Utility function to generate a pseudo random number. */

	ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
	return( ( int ) ( ulNextRand >> 16UL ) & 0x7fffUL );
}

void vLoggingPrintf( const char *pcFormatString, ... )
{
	return;
}

uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
													uint16_t usSourcePort,
													uint32_t ulDestinationAddress,
													uint16_t usDestinationPort ){
	return 306;
}

/*
 * Supply a random number to FreeRTOS+TCP stack.
 * THIS IS ONLY A DUMMY IMPLEMENTATION THAT RETURNS A PSEUDO RANDOM NUMBER
 * SO IS NOT INTENDED FOR USE IN PRODUCTION SYSTEMS.
 */
BaseType_t xApplicationGetRandomNumber(uint32_t* pulNumber)
{
	*(pulNumber) = uxRand();
	return pdTRUE;
}

void vAssertCalled( uint32_t ulLine, const char *pcFile )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	taskENTER_CRITICAL();
	{
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			__NOP();
		}
	}
	taskEXIT_CRITICAL();
}

/* print string over usart1 */
void debugPrint(char _out[]){
	/* disable interrupts */
	vPortEnterCritical();
	HAL_UART_Transmit(&huart1, (uint8_t *) _out, strlen(_out), 10);
	/* enable interrupts */
	vPortExitCritical();
}

/* print string over usart1 with \r\n */
void debugPrintln(char _out[]){
	/* disable interrupts */
	vPortEnterCritical();
	HAL_UART_Transmit(&huart1, (uint8_t *) _out, strlen(_out), 10);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t *) newline, 2, 10);
	/* enable interrupts */
	vPortExitCritical();
}

/* iterate over an array and check if all members are True (1) */
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

/* set all members of array to False (0) */
void resetBoolArray ( unsigned char* receivedPackets )
{
	for (int entry = 0; entry < EPOCHES; entry++)
	{
		receivedPackets[entry] = 0;
	}
}
