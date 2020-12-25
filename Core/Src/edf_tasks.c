/* description */


#include <user_variables.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"


/* struct with preferences for a EDF Task */
struct edfTaskStruct_s
{
	TaskHandle_t* taskHandle;
	const char* taskName;
	TickType_t capacity;				// capacity or worst-case computation time
	TickType_t period;					// The priority at which the created task will execute
	TickType_t relativeDeadline;		// task relative deadline, i.e. the maximum acceptable delay for its processing
	TickType_t absoluteDeadline;		// task absolute deadline
	TickType_t lastRunningTime;			// last time running
	TickType_t startTime;				// time when starts the task
	TickType_t stopTime;				// time when task has finished
	uint32_t callCounter;				// how often was the task executed
}edfTaskStructDefault = {NULL, "default", 0, 0, 0, 0, 0, 0, 0, 0};

typedef struct edfTaskStruct_s edfTaskStruct;

/* define globals */
/* global struct of all EDF Tasks */
struct edfTasksStruct
{
	edfTaskStruct tasksArray[SIZE_OF_EDF_TASKS_ARRAY];
	unsigned int numberOfEDFTasks;
}edfTasks = {NULL, 0};


/* initialisation of edfTasksStruct */
void initEDFTasksStruct( void )
{
	for( int i = 0; i < SIZE_OF_EDF_TASKS_ARRAY; i++ )
	{
		edfTasks.tasksArray[i] = edfTaskStructDefault;
	}
}



BaseType_t createEDFTask( TaskFunction_t taskCode,					// Pointer to the task entry function
						  const char* taskName,						// A descriptive name for the task
						  configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
						  void* pvParameters,						// A value that will passed into the created task as the task`s parameter
						  TickType_t capacity,						// Capacity or worst-case computation time
						  TickType_t period)						// Period of Task
{
	unsigned int edfTaskNumber = edfTasks.numberOfEDFTasks;
	BaseType_t xReturned = xTaskCreate( taskCode, taskName, stackDepth , NULL, EDF_DISABLED_PRIORITY, edfTasks.tasksArray[edfTaskNumber].taskHandle );
	edfTasks.tasksArray[edfTaskNumber].taskName = taskName;
	edfTasks.tasksArray[edfTaskNumber].capacity = capacity;
	edfTasks.tasksArray[edfTaskNumber].period = period;
	return xReturned;
}
