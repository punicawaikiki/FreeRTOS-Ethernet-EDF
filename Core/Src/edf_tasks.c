/* description */

#include "edf_tasks.h"
#include <user_variables.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "helper_functions.h"
#include "stdio.h"

edfTasks_s edfTasks;

#if DEBUG_MODE
	// counting edf scheduler errors (deadline couldn`t passed)
	static uint32_t timeError = 0;
#endif

//#if DEBUG_MODE
//	TickType_t calcLastRunningTime( void )
//	{
//		edfTasks
//		return edfTasks.tasksArray[edfTasks.activeTask].stopTime - edfTasks.tasksArray[edfTasks.activeTask].startTime;
//	}
//#endif

//// Prototypes
//void vApplicationIdleHook( void );
//TickType_t calcShortestDeadline( void );
//void rescheduleEDF( void );
//BaseType_t createEDFTask( TaskFunction_t taskCode,					// Pointer to the task entry function
//						  const char* taskName,						// A descriptive name for the task
//						  configSTACK_DEPTH_TYPE stackDepth,		// The number of words (not bytes!) to allocate for use as the task`s stack
//						  void* pvParameters,						// A value that will passed into the created task as the task`s parameter
//						  TickType_t capacity,						// Capacity or worst-case computation time
//						  TickType_t period,						// Period of Task
//						  TickType_t deadline);						// Deadline of Task

//	this hook is called if no task is in ready state
void vApplicationIdleHook( void )
{
	for( ;; )
	{
//		if (numberOfEDFTasks > 0)
//		{
//			rescheduleEDF();
//		}
	}
}


TickType_t calcShortestDeadline( void )
{
	TickType_t currentTick = xTaskGetTickCount();
	// buffer for initialization of shortest latestStartTime
	uint32_t initTaskNumber = 0;
	// init shortest latestStartTime buffer variable
	TickType_t shortestLatestStartTime;
	// save task number with negative value, -1 means something went wrong
	uint32_t shortestDeadlineTask = -1;
	// iterate over all EDF tasks
	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		// if the latest Start Time of task is lower than current tick, the task will be updated and ignored for this schedule step
		if ( currentTick > edfTasks.tasksArray[taskCounter].latestStartTime )
		{
			#if DEBUG_MODE
				char buffer[100];
				timeError++;
				snprintf(buffer, sizeof(buffer), "ERROR lastStartTime of Task: %s couldn`t reached (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, timeError);
				debugPrintln(buffer);
			#endif
			initTaskNumber++;
			edfTasks.tasksArray[taskCounter].latestStartTime = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline
					- edfTasks.tasksArray[taskCounter].wcet;
			edfTasks.tasksArray[taskCounter].absoluteDeadline = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline;
			continue;
		}
		// if first task copy latestStartTime from first task as initialization
		if ( taskCounter == initTaskNumber )
		{
			shortestLatestStartTime = edfTasks.tasksArray[taskCounter].latestStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// compare current task so far to the shortest latestStartTime
		else if ( edfTasks.tasksArray[taskCounter].latestStartTime < shortestLatestStartTime )
		{
			shortestLatestStartTime = edfTasks.tasksArray[taskCounter].latestStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// should two tasks have the same latestStartTime, the task with lower callCounter would get the higher priority
		else if ( edfTasks.tasksArray[taskCounter].latestStartTime == shortestLatestStartTime )
		{
			if ( edfTasks.tasksArray[taskCounter].callCounter < edfTasks.tasksArray[shortestDeadlineTask].callCounter)
			{
				shortestLatestStartTime = edfTasks.tasksArray[taskCounter].latestStartTime;
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


/* reschedule edf tasks
 * Max execution time with debug mode on: 3 Ticks
 * Max execution time with debug mode off: 2 Ticks
 *  */
void rescheduleEDF( void )
{
	TickType_t currentTick = xTaskGetTickCount();
	#if DEBUG_MODE
		// set current Tick to edfTasks struct
		edfTasks.currentTick = currentTick;
	#endif
	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		if ( edfTasks.tasksArray[taskCounter].latestStartTime > ( currentTick + edfTasks.tasksArray[taskCounter].relativeDeadline))
		{
			vTaskPrioritySet( edfTasks.tasksArray[taskCounter].taskHandle, EDF_DISABLED_PRIORITY );
		}
		#if DEBUG_MODE
			else if ( edfTasks.tasksArray[taskCounter].latestStartTime < currentTick )
			{
				char buffer[100];
				timeError++;
				snprintf(buffer, sizeof(buffer), "ERROR lastStartTime of Task: %s couldn`t reached (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, timeError);
				debugPrintln(buffer);
			}
		#endif
		else
		{
			// check if callCounter of task reach max of uint32_t
			if (edfTasks.tasksArray[taskCounter].callCounter == UINT32_MAX)
			{
				// prevent overflow -> set callCounter to zero
				edfTasks.tasksArray[taskCounter].callCounter = 0;
				#if DEBUG_MODE
					char buffer[100];
					snprintf(buffer, sizeof(buffer), "CallCounter of Task: %s resettet to 0 (prevent overflow)", edfTasks.tasksArray[taskCounter].taskName );
					debugPrintln("ERROR in calcShortestDeadline");
				#endif
			}
			else
			{
				// increase task call counter
				edfTasks.tasksArray[taskCounter].callCounter++;
			}
			// calculate next latest start time of task
			edfTasks.tasksArray[taskCounter].latestStartTime = edfTasks.tasksArray[taskCounter].latestStartTime
					+ edfTasks.tasksArray[taskCounter].period;
			#if DEBUG_MODE
				// calculate next absolute deadline of task
				edfTasks.tasksArray[taskCounter].absoluteDeadline = edfTasks.tasksArray[taskCounter].absoluteDeadline
						+ edfTasks.tasksArray[taskCounter].period;
//				// set stop time
//				edfTasks.tasksArray[taskCounter].stopTime = xTaskGetTickCount();
//				// calculate running time if after task was one time called
//				if ( edfTasks.tasksArray[taskCounter].callCounter > 10)
//				{
//					edfTasks.tasksArray[taskCounter].lastRunningTime = calcLastRunningTime();
//				}
//				// trace max execution time
//				if (edfTasks.tasksArray[taskCounter].lastRunningTime > edfTasks.tasksArray[taskCounter].maxRunningTime)
//				{
//					edfTasks.tasksArray[taskCounter].maxRunningTime = edfTasks.tasksArray[taskCounter].lastRunningTime;
//				}
			#endif
			// find shortest deadline task number
			TickType_t shortestDeadlineTask = calcShortestDeadline();
//			#if DEBUG_MODE
//				// set startTime of task
//				edfTasks.tasksArray[shortestDeadlineTask].startTime = xTaskGetTickCount();
//			#endif
			// set the priority of the next task one higher to get running
			vTaskPrioritySet( edfTasks.tasksArray[shortestDeadlineTask].taskHandle, EDF_ENABLED_PRIOTIRY);
			// set task number in edf struct
			edfTasks.activeTask = shortestDeadlineTask;
			#if DEBUG_MODE
				edfTasks.cet = xTaskGetTickCount() - currentTick;
				if ( edfTasks.cet > edfTasks.wcet )
				{
					edfTasks.wcet = edfTasks.cet;
				}
			#endif
			break;
		}
	}
		// force context switch if not happend
	taskYIELD();
}

void edfIdleTask( void *pvParameters )
{
	while(1)
	{
		rescheduleEDF();
	}
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
	uint32_t edfTaskNumber = edfTasks.numberOfEDFTasks;
	// set realtiveDeadline
	edfTasks.tasksArray[edfTaskNumber].relativeDeadline = deadline;
	// calculate next deadline
	edfTasks.tasksArray[edfTaskNumber].absoluteDeadline = currentTick + deadline;
	// calculate latest start time
	edfTasks.tasksArray[edfTaskNumber].latestStartTime = currentTick + deadline - capacity;
	// status of task creation
	BaseType_t xReturned;
	// create normal freeRTOS task
	if ( edfTasks.numberOfEDFTasks == 0)
	{
		xReturned = xTaskCreate( taskCode, taskName, stackDepth , NULL, EDF_ENABLED_PRIOTIRY, &edfTasks.tasksArray[edfTaskNumber].taskHandle );
	}
	else
	{
		xReturned = xTaskCreate( taskCode, taskName, stackDepth , NULL, EDF_DISABLED_PRIORITY, &edfTasks.tasksArray[edfTaskNumber].taskHandle );
	}
	// set task name
	edfTasks.tasksArray[edfTaskNumber].taskName = taskName;
	// set capacity of task
	edfTasks.tasksArray[edfTaskNumber].wcet = capacity;
	// set period of task
	edfTasks.tasksArray[edfTaskNumber].period = period;
	if (edfTasks.numberOfEDFTasks == 0)
	{
		xTaskCreate( edfIdleTask, "EDF Idle Task", 100 , NULL, EDF_IDLE_PRIORITY, &edfTasks.idleTask );
	}
	// increment number of tasks
	edfTasks.numberOfEDFTasks++;
	// return pdTrue if task creation was successful, pdFalse when not
	return xReturned;
}
