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

TickType_t calcShortestDeadline( void )
{

	// init shortest latestStartTime buffer variable
	TickType_t shortestDeadline;
	// save task number with negative value, -1 means something went wrong
	unsigned int shortestDeadlineTask = -1;
	// iterate over all EDF tasks
	for (unsigned int taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		// if first task copy latestStartTime from first task as initialization
		if ( taskCounter == 0 )
		{
			shortestDeadline = edfTasks.tasksArray[taskCounter].latestStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// compare current task so far to the shortest latestStartTime
		else if ( edfTasks.tasksArray[taskCounter].latestStartTime < shortestDeadline )
		{
			shortestDeadline = edfTasks.tasksArray[taskCounter].latestStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// should two tasks have the same latestStartTime, the task with lower callCounter would get the higher priority
		else if ( edfTasks.tasksArray[taskCounter].latestStartTime == shortestDeadline )
		{
			if ( edfTasks.tasksArray[taskCounter].callCounter < edfTasks.tasksArray[shortestDeadlineTask].callCounter)
			{
				shortestDeadline = edfTasks.tasksArray[taskCounter].latestStartTime;
				shortestDeadlineTask = taskCounter;
			}
		}
	}
	// should never send this error message
	if ( (shortestDeadlineTask < 0) || ( shortestDeadlineTask > (SIZE_OF_EDF_TASKS_ARRAY -1)) )
	{
		while(1)
		{
			char buffer[100];
			snprintf(buffer, sizeof(buffer), "ERROR in calcShortestDeadline @%lu", xTaskGetTickCount() );
			debugPrintln("ERROR in calcShortestDeadline");
		}
	}
	else
	{
		// return task number which has the next shortest deadline
		return shortestDeadlineTask;
	}
}


TickType_t calcLastRunningTime( void )
{
	return edfTasks.tasksArray[edfTasks.activeTask].stopTime - edfTasks.tasksArray[edfTasks.activeTask].startTime;
}

TickType_t calcLatestStartTime( TickType_t currentTick )
{
	return currentTick + edfTasks.tasksArray[edfTasks.activeTask].relativeDeadline - edfTasks.tasksArray[edfTasks.activeTask].capacity;
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
	TickType_t currentTick = xTaskGetTickCount();
	// set stop time
	edfTasks.tasksArray[edfTasks.activeTask].stopTime = currentTick;
	// calculate running time
	edfTasks.tasksArray[edfTasks.activeTask].lastRunningTime = calcLastRunningTime();
	// calculate next latest start time of task
	edfTasks.tasksArray[edfTasks.activeTask].latestStartTime = calcLatestStartTime( currentTick );
	// calculate next deadline of task
	edfTasks.tasksArray[edfTasks.activeTask].absoluteDeadline = calcNextDeadline( currentTick );
	// find shortest deadline task number
	unsigned int shortestDeadlineTask = calcShortestDeadline();
	// set startTime of task
	// edfTasks.tasksArray[shortestDeadlineTask].startTime = xTaskGetTickCount();
	edfTasks.tasksArray[shortestDeadlineTask].startTime = currentTick;
	// increase task call counter
	edfTasks.tasksArray[shortestDeadlineTask].callCounter++;
	// set task numer in edf struct
	edfTasks.activeTask = shortestDeadlineTask;
	// set current task to lower priority if the next shortest deadline is the same task
	if ( executedTask != shortestDeadlineTask )
	{
		// set the priority of last task one prio lower than the task which need to be executed next
		vTaskPrioritySet( edfTasks.tasksArray[executedTask].taskHandle, EDF_DISABLED_PRIORITY);
		// set the priority of the next task one higher to get running
		vTaskPrioritySet( edfTasks.tasksArray[shortestDeadlineTask].taskHandle, EDF_ENABLED_PRIOTIRY);
		// force context switch (why should we wait for sysTick)
		taskYIELD();
	}
}


/* initialisation of edfTasksStruct */
void initEDFTasksStruct( void )
{
	// get shortest deadline task number
	unsigned int shortestDeadlineTask = calcShortestDeadline();
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
