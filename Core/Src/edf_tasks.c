/* description */


#include <user_variables.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "helper_functions.h"
#include "stdio.h"


/* struct with preferences for a EDF Task */
struct edfTaskStruct_s
{
	TaskHandle_t taskHandle;
	const char* taskName;
	TickType_t capacity;				// capacity or worst-case computation time
	TickType_t period;					// The priority at which the created task will execute
	TickType_t latestStartTime;			// task relative deadline, i.e. the maximum acceptable delay for its processing
	TickType_t absoluteDeadline;	    // task absolute deadline
	TickType_t relativeDeadline;		// task relative deadline
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
	edfTaskStruct tasksArray[SIZE_OF_EDF_TASKS_ARRAY];	// tasks array
	unsigned long lastExecutionTime;					// last execution time of rescheduling EDF
	unsigned int numberOfEDFTasks;						// total number of tasks
	unsigned int activeTask;							// display active task number
}edfTasks;

unsigned int shortestDeadline( void )
{
	// init function variable with high value, 100000 means something went wrong
	int shortestDeadline = 1000000;
	// save task number with negative value, -1 means something went wrong
	int shortestDeadlineTask = -1;
	// iterate over all EDF tasks
	for (int taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		if ( edfTasks.tasksArray[taskCounter].absoluteDeadline < shortestDeadline )
		{
			shortestDeadline = edfTasks.tasksArray[taskCounter].absoluteDeadline;
			shortestDeadlineTask = taskCounter;
		}
	}
	if ( (shortestDeadlineTask == -1 ) )
	{
		#if DEBUG_MODE
			debugPrintln("shortestDeadline error");
		#endif
		// something went wrong
		return -9999;
	}
	else
	{
		// return shortest deadline task
		return shortestDeadlineTask;
	}
}


TickType_t calcLastRunningTime( void )
{
	return edfTasks.tasksArray[edfTasks.activeTask].stopTime - edfTasks.tasksArray[edfTasks.activeTask].startTime;
}

TickType_t calcLatestStartTime( void )
{
	return edfTasks.tasksArray[edfTasks.activeTask].absoluteDeadline + edfTasks.tasksArray[edfTasks.activeTask].absoluteDeadline - edfTasks.tasksArray[edfTasks.activeTask].capacity;
}

TickType_t calcNextDeadline( TickType_t currentTick )
{
	return currentTick + edfTasks.tasksArray[edfTasks.activeTask].relativeDeadline;
}

/* reschedule edf tasks */
void rescheduleEDF( void )
{
	// executed task
	unsigned int executedTask = edfTasks.activeTask;
	// get current tick
	uint32_t currentTick = xTaskGetTickCount();
	// set stop time
	edfTasks.tasksArray[edfTasks.activeTask].stopTime = currentTick;
	// calculate running time
	edfTasks.tasksArray[edfTasks.activeTask].lastRunningTime = calcLastRunningTime();
	// calculate next latest start time of task
	edfTasks.tasksArray[edfTasks.activeTask].latestStartTime = calcLatestStartTime();
	// calculate next deadline of task
	edfTasks.tasksArray[edfTasks.activeTask].absoluteDeadline = calcNextDeadline( currentTick );
	// find shortest deadline task number
	unsigned int shortestDeadlineTask = shortestDeadline();
	// set startTime of task
	edfTasks.tasksArray[shortestDeadlineTask].startTime = xTaskGetTickCount();
	// increase task call counter
	edfTasks.tasksArray[shortestDeadlineTask].callCounter++;
	// set task numer in edf struct
	edfTasks.activeTask = shortestDeadlineTask;

	vTaskPrioritySet( edfTasks.tasksArray[executedTask].taskHandle, EDF_DISABLED_PRIORITY);
	vTaskPrioritySet( edfTasks.tasksArray[shortestDeadlineTask].taskHandle, EDF_ENABLED_PRIOTIRY);
	#if DEBUG_MODE
		char buffer[100];
		unsigned long t1 = uxTaskPriorityGet( edfTasks.tasksArray[executedTask].taskHandle );
		unsigned long t2 = uxTaskPriorityGet( edfTasks.tasksArray[shortestDeadlineTask].taskHandle );
		snprintf(buffer, sizeof(buffer), "Prio of Task1: %lu, Task2: %lu", t1, t2 );
		debugPrintln(buffer);
	#endif
	// resume selected task
	vTaskResume( edfTasks.tasksArray[shortestDeadlineTask].taskHandle );
	// suspend current task
	vTaskSuspend( NULL );
}


/* initialisation of edfTasksStruct */
void initEDFTasksStruct( void )
{
	// get shortest deadline task number
	unsigned int shortestDeadlineTask = shortestDeadline();
	// set startTime of task
	edfTasks.tasksArray[shortestDeadlineTask].startTime = xTaskGetTickCount();
	// increase task call counter
	edfTasks.tasksArray[shortestDeadlineTask].callCounter++;
	// set task numer in edf struct
	edfTasks.activeTask = shortestDeadlineTask;
//	// resume selected task
//	vTaskResume( edfTasks.tasksArray[shortestDeadlineTask].taskHandle );
//	vTaskPrioritySet(edfTasks.tasksArray[shortestDeadlineTask].taskHandle, EDF_ENABLED_PRIOTIRY);
	#if DEBUG_MODE
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "initEDFTasksStruct finished, selected Task: %d", shortestDeadlineTask );
		debugPrintln(buffer);
	#endif
}

BaseType_t createEDFTask( TaskFunction_t taskCode,					// Pointer to the task entry function
						  const char* taskName,						// A descriptive name for the task
						  configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
						  void* pvParameters,						// A value that will passed into the created task as the task`s parameter
						  TickType_t capacity,						// Capacity or worst-case computation time
						  TickType_t period,						// Period of Task
						  TickType_t deadline)						// Deadline of Task
{
	// get current Tick
	uint32_t currentTick = xTaskGetTickCount();
	// get current number of tasks
	unsigned int edfTaskNumber = edfTasks.numberOfEDFTasks;
	// set realtiveDeadline
	edfTasks.tasksArray[edfTaskNumber].relativeDeadline = deadline;
	// calculate next deadline
	edfTasks.tasksArray[edfTaskNumber].absoluteDeadline = currentTick + deadline;
	// calculate latest start time
	edfTasks.tasksArray[edfTaskNumber].latestStartTime = currentTick + deadline - capacity;
	// create normal freeRTOS task
	BaseType_t xReturned = xTaskCreate( taskCode, taskName, stackDepth , NULL, EDF_DISABLED_PRIORITY, &edfTasks.tasksArray[edfTaskNumber].taskHandle );
	// set task name
	edfTasks.tasksArray[edfTaskNumber].taskName = taskName;
	// set capacity of task
	edfTasks.tasksArray[edfTaskNumber].capacity = capacity;
	// set period of task
	edfTasks.tasksArray[edfTaskNumber].period = period;
//	// set task to suspend mode
//	vTaskSuspend(edfTasks.tasksArray[edfTaskNumber].taskHandle);
	// increment number of tasks
	edfTasks.numberOfEDFTasks++;
	// update last execution time
	edfTasks.lastExecutionTime = xTaskGetTickCount();
	// return pdTrue if task creation was successful, pdFalse when not
	return xReturned;
}
