/* description */


#include <user_variables.h>
#include "FreeRTOS.h"
#include "main.h"


/* define globals */


BaseType_t createEDFTask( TaskFunction_t taskCode,				// Pointer to the task entry function
						  const char* taskName,					// A descriptive name for the task
						  configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
						  void* pvParameters,						// A value that will passed into the created task as the task`s parameter
						  TickType_t capacity,					// Capacity or worst-case computation time
						  TickType_t period)						// Period of Task
{



}
