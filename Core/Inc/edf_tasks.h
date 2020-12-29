/* Description */

#ifndef __EDF_TASK_H
#define __EDF_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


#define SIZE_OF_EDF_TASKS_ARRAY 3
#define EDF_DISABLED_PRIORITY configMAX_PRIORITIES - 3
#define EDF_IDLE_PRIORITY configMAX_PRIORITIES - 2
#define EDF_ENABLED_PRIOTIRY configMAX_PRIORITIES - 1


/* struct with preferences for a EDF Task */
typedef struct
{
	TaskHandle_t taskHandle;
	const char* taskName;
	TickType_t wcet;						// worst compution execution time
	TickType_t period;						// The priority at which the created task will execute
	TickType_t latestStartTime;				// task relative deadline, i.e. the maximum acceptable delay for its processing
	TickType_t absoluteDeadline;	    	// task absolute deadline
	TickType_t relativeDeadline;			// task relative deadline
	#if DEBUG_MODE
		TickType_t lastRunningTime;			// last time running
		TickType_t maxRunningTime;					// maximum task execution time
		TickType_t startTime;				// time when starts the task
		TickType_t stopTime;				// time when task has finished
	#endif
	uint32_t callCounter;					// how often was the task executed
}edfTaskStruct;

//#if DEBUG_MODE
//	edfTaskStruct = {NULL, "default", 0, 0, 0, 0, 0, 0, 0, 0};
//#else
//	edfTaskStruct = {NULL, "default", 0, 0, 0, 0, 0};
//#endif



/* define globals */
/* global struct of all EDF Tasks */
typedef struct
{
	edfTaskStruct tasksArray[SIZE_OF_EDF_TASKS_ARRAY];	// tasks array
	TaskHandle_t idleTask;								// idle task used when nothing to do
	unsigned int numberOfEDFTasks;						// total number of tasks
	unsigned int activeTask;							// display active task number
	#if DEBUG_MODE
	TickType_t currentTick;								// current tick of edfScheduler
	TickType_t wcet;									// worst execution time
	TickType_t cet;										// current execution time
	#endif
}edfTasks_s;


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
BaseType_t createEDFTask( TaskFunction_t taskCode,					// Pointer to the task entry function
						  const char* taskName,						// A descriptive name for the task
						  configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
						  void* pvParameters,						// A value that will passed into the created task as the task`s parameter
						  TickType_t capacity,						// Capacity or worst-case computation time
						  TickType_t period,						// Period of Task
						  TickType_t deadline);						// Deadline of Task


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

// Return Type: void
// Name: vApplicationIdleHook
// Parameters: void
// Declaration
void vApplicationIdleHook(void);



#endif /* __EDF_TASK_H */
