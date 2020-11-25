/* This File includes all defined hooks */

#ifndef __HOOKS_H
#define __HOOKS_H


#include "FreeRTOS.h"
#include "FreeRTOS_IP.h"


/* Define HOST NAME */
#define mainHOST_NAME					"RTOSDemo"
#define mainDEVICE_NICK_NAME			"stm32"
#define standardTASK_PRIORITY          ( tskIDLE_PRIORITY )


// Return Type: const char*
// Name: pcApplicationHostnameHook
// Parameters: void
// Declaration
const char *pcApplicationHostnameHook( void );

// Return Type: BaseType_t
// Name: xApplicationDNSQueryHook
// Parameters: const char *pcName
// Declaration
BaseType_t xApplicationDNSQueryHook( const char *pcName );

// Return Type: void
// Name: vApplicationIPNetworkEventHook
// Parameters: eIPCallbackEvent_t eNetworkEvent
// Declaration
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent );


#endif /* __HOOKS_H */
