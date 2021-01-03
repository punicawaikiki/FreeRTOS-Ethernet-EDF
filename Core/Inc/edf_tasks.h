/* Description */

#ifndef __EDF_TASK_H
#define __EDF_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

// defines the maximum number of edf tasks
#define MAX_EDF_TASKS 10


#define EDF_DISABLED_PRIORITY tskIDLE_PRIORITY
#define EDF_IDLE_PRIORITY tskIDLE_PRIORITY + 1
#define EDF_ENABLED_PRIOTIRY tskIDLE_PRIORITY + 2
#define EDF_SCHEDULE_PRIORITY tskIDLE_PRIORITY + 3

//#define EDF_DISABLED_PRIORITY configMAX_PRIORITIES - 4
//#define EDF_IDLE_PRIORITY configMAX_PRIORITIES - 3
//#define EDF_ENABLED_PRIOTIRY configMAX_PRIORITIES - 2
//#define EDF_SCHEDULE_PRIORITY configMAX_PRIORITIES - 1


/* struct with preferences for a EDF Task */
typedef struct
{
	TaskHandle_t taskHandle;				// task handle
	const char* taskName;					// task name
	BaseType_t taskCreated;					// flag to see if task is created
	TickType_t wcet;						// worst compution execution time
	TickType_t period;						// The priority at which the created task will execute
	TickType_t lastStartTime;				// task relative deadline, i.e. the maximum acceptable delay for its processing
	TickType_t absoluteDeadline;	    	// task absolute deadline
	TickType_t relativeDeadline;			// task relative deadline
	uint32_t callCounter;					// how often was the task executed
	#if DEBUG_MODE
		TickType_t lastRunningTime;			// last time running
		TickType_t maxRunningTime;			// maximum task execution time
		TickType_t startTime;				// time when starts the task
		TickType_t stopTime;				// time when task has finished
		uint32_t deadlineErrorCounter;		// increase when deadline missed
	#endif
}edfTaskStruct;


/* define globals */
/* global struct of all EDF Tasks */
typedef struct
{
	edfTaskStruct tasksArray[MAX_EDF_TASKS];			// tasks array
	TaskHandle_t idleTask;								// idle task used when nothing to do
	BaseType_t idleTaskCreated;							// flag to signal if freeRTOS idle Task is optimized for EDF
	unsigned int numberOfEDFTasks;						// total number of tasks
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


// Return Type: void
// Name: rescheduleEDF
// Parameters: void
// Declaration
void rescheduleEDF ( void );

// Return Type: BaseType_t
// Name: deleteEDFTask
// Parameters: const char* taskName
// Declaration
void deleteEDFTask( const char* taskName);

// Return Type: void
// Name: vApplicationIdleHook
// Parameters: void
// Declaration
void vApplicationIdleHook(void);


#endif /* __EDF_TASK_H */
