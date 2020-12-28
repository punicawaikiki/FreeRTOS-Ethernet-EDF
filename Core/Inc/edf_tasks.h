/* Description */

#ifndef __EDF_TASK_H
#define __EDF_TASK_H

#include "FreeRTOS.h"
#include "task.h"


// Return Type: void
// Name: initEDFTasksStruct
// Parameters: void
// Declaration
void initEDFTasksStruct( void );



/* Return Type: BaseType_t
 * Name: createEDFTask
 * Parameters:
 *  - TaskFunction_t taskCode
 *  - const char* taskName
 *  - configSTACK_DEPTH_TYPE stackDepth
 *  - void* pvParameters
 *  - TickType_t capacity
 *  - TickType_t period
 * Declaration
 */
void createEDFTask( TaskFunction_t taskCode,				// Pointer to the task entry function
				    const char* taskName,					// A descriptive name for the task
				    configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
				    void* pvParameters,						// A value that will passed into the created task as the task`s parameter
				    TickType_t capacity,					// Capacity or worst-case computation time
				    TickType_t period,						// Period of Task);
					TickType_t deadline);					// deadline of Task


// Return Type: TickType_t
// Name: calcShortestDeadline
// Parameters: void
// Declaration
TickType_t calcShortestDeadline( void );

// Return Type: void
// Name: rescheduleEDF
// Parameters: void
// Declaration
void rescheduleEDF ( void );


#endif /* __EDF_TASK_H */
