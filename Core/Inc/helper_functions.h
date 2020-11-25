/* Functions for cummunicate with the UDP Interface*/

#ifndef __HELPER_FUNCTIONS_H
#define __HELPER_FUNCTIONS_H


#include "FreeRTOS.h"
#include "portmacro.h"


/* Use by the pseudo random number generator. */
UBaseType_t ulNextRand;


// Return Type: void
// Name: prvSRand
// Parameters: UBaseType_t ulSeed
// Declaration
void prvSRand( UBaseType_t ulSeed );

// Return Type: UBaseType_t
// Name: uxRand
// Parameters: void
// Declaration
UBaseType_t uxRand( void );

// Return Type: void
// Name: vLoggingPrintf
// Parameters: const char *pcFormatString, ...
// Declaration
void vLoggingPrintf( const char *pcFormatString, ... );

// Return Type: uint32_t
// Name: ulApplicationGetNextSequenceNumber
// Parameters: uint32_t ulSourceAddress,
//				uint16_t usSourcePort,
// 				uint32_t ulDestinationAddress,
//				uint16_t usDestinationPort
// Declaration
uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
													uint16_t usSourcePort,
													uint32_t ulDestinationAddress,
													uint16_t usDestinationPort );

// Return Type: BaseType_t
// Name: xApplicationGetRandomNumber
// Parameters: uint32_t* pulNumber
// Declaration
BaseType_t xApplicationGetRandomNumber(uint32_t* pulNumber);

// Return Type: void
// Name: vAssertCalled
// Parameters: uint32_t ulLine, const char *pcFile
// Declaration
void vAssertCalled( uint32_t ulLine, const char *pcFile );


#endif /* __HELPER_FUNCTIONS_H */
