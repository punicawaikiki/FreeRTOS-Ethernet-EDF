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


//	this hook is called if no task is in ready state
void vApplicationIdleHook( void )
{
	for( ;; );
}


TickType_t calcShortestDeadline( void )
{
	TickType_t currentTick = xTaskGetTickCount();
	// buffer for initialization of shortest latestStartTime
	uint32_t initTaskNumber = 0;
	// init shortest latestStartTime buffer variable
	TickType_t shortestLastStartTime;
	// save task number with negative value, -1 means something went wrong
	uint32_t shortestDeadlineTask = -1;
	// iterate over all EDF tasks
	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		// if the latest Start Time of task is lower than current tick, the task will be updated and ignored for this schedule step
		if ( currentTick > edfTasks.tasksArray[taskCounter].lastStartTime )
		{
			#if DEBUG_MODE
				// increase debug variable
				edfTasks.tasksArray[taskCounter].deadlineErrorCounter++;
				char buffer[100];
				timeError++;
				snprintf(buffer, sizeof(buffer), "ERROR lastStartTime of Task: %s couldn`t reached (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, timeError);
				debugPrintln(buffer);
			#endif
			// check if task was initial task, true -> increase initTaskNumber
			initTaskNumber++;
			// calc last start time of current task
			edfTasks.tasksArray[taskCounter].lastStartTime = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline
					- edfTasks.tasksArray[taskCounter].wcet;
			// calc absolute deadline of current task
			edfTasks.tasksArray[taskCounter].absoluteDeadline = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline;
			// go to the next task in array
			continue;
		}
		// if first task copy lastStartTime from first task as initialization
		if ( taskCounter == initTaskNumber )
		{
			shortestLastStartTime = edfTasks.tasksArray[taskCounter].lastStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// compare current task so far to the shortest lastStartTime
		else if ( edfTasks.tasksArray[taskCounter].lastStartTime < shortestLastStartTime )
		{
			shortestLastStartTime = edfTasks.tasksArray[taskCounter].lastStartTime;
			shortestDeadlineTask = taskCounter;
		}
		// should two tasks have the same lastStartTime, the task with lower callCounter would get the higher priority
		else if ( edfTasks.tasksArray[taskCounter].lastStartTime == shortestLastStartTime )
		{
			if ( edfTasks.tasksArray[taskCounter].callCounter < edfTasks.tasksArray[shortestDeadlineTask].callCounter)
			{
				shortestLastStartTime = edfTasks.tasksArray[taskCounter].lastStartTime;
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
	// get current tick of system
	TickType_t currentTick = xTaskGetTickCount();
	// init shortest lastStartTime buffer variable
	TickType_t shortestLastStartTimeTask = -1;
	// suspend task itself?
	uint32_t suspendSelf = 0;
	// buffer for initialization of shortest lastStartTime
	uint32_t initTaskNumber = 0;
	#if DEBUG_MODE
		// set current Tick to edfTasks struct
		edfTasks.currentTick = currentTick;
	#endif
	// iterate over all tasks and get shortest lastStartTime task
	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{
		// deadline could not reached, restart Task (if DEBUG_MODE is on print ERROR)
		if( edfTasks.tasksArray[taskCounter].lastStartTime < currentTick )
		{
			// increase initial task number
			initTaskNumber++;
			// calc next last start time of current task based on current tick
			edfTasks.tasksArray[taskCounter].lastStartTime = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline
					- edfTasks.tasksArray[taskCounter].wcet;
			// calc absolute deadline of current task based on current tick
			edfTasks.tasksArray[taskCounter].absoluteDeadline = currentTick
					+ edfTasks.tasksArray[taskCounter].relativeDeadline;
			#if DEBUG_MODE
				// increase debug variable
				edfTasks.tasksArray[taskCounter].deadlineErrorCounter++;
				char buffer[100];
				snprintf(buffer, sizeof(buffer), "ERROR lastStartTime of Task: %s couldn`t reached (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, edfTasks.tasksArray[taskCounter].deadlineErrorCounter);
				debugPrintln(buffer);
			#endif
		}
		// is deadline longer as relativeDeadline away task status set to suspended
		if( edfTasks.tasksArray[taskCounter].lastStartTime > ( currentTick + edfTasks.tasksArray[taskCounter].relativeDeadline ) )
		{
			// increase initial task number
			initTaskNumber++;
			// set task status to suspended
			edfTasks.tasksArray[taskCounter].taskReady = pdFALSE;
		}
		// set initial task to compare lastStartTime of all tasks
		else if( taskCounter == initTaskNumber)
		{
			shortestLastStartTimeTask = taskCounter;
		}
		// is current task lastStartTime earlier than the earlierst yet?
		else if( edfTasks.tasksArray[taskCounter].lastStartTime < edfTasks.tasksArray[shortestLastStartTimeTask].lastStartTime )
		{
			shortestLastStartTimeTask = taskCounter;
		}
		// if lastStartTime equal, set task which has lower callCounter
		else if( edfTasks.tasksArray[taskCounter].lastStartTime == edfTasks.tasksArray[shortestLastStartTimeTask].lastStartTime )
		{
			if ( edfTasks.tasksArray[taskCounter].lastStartTime < edfTasks.tasksArray[shortestLastStartTimeTask].callCounter)
			{
				shortestLastStartTimeTask = taskCounter;
			}
		}
		// should never reached
		else
		{
			debugPrintln("ERROR: couldn`t determine lastStartTime of Task!");
		}
	}
	// should never reached
	if ( shortestLastStartTimeTask == -1)
	{
		debugPrintln("ERROR: shortestLastStartTimeTask not set!");
	}
	// check if callCounter of task reach max of uint32_t
	if (edfTasks.tasksArray[shortestLastStartTimeTask].callCounter == UINT32_MAX)
	{
		// prevent overflow -> set callCounter to zero
		edfTasks.tasksArray[shortestLastStartTimeTask].callCounter = 0;
		#if DEBUG_MODE
			char buffer[100];
			snprintf(buffer, sizeof(buffer), "CallCounter of Task: %s resettet to 0 (prevent overflow)", edfTasks.tasksArray[shortestLastStartTimeTask].taskName );
			debugPrintln("ERROR in calcShortestDeadline");
		#endif
	}
	else
	{
		// increase task call counter
		edfTasks.tasksArray[shortestLastStartTimeTask].callCounter++;
	}
	// calculate next latest start time of task
	edfTasks.tasksArray[shortestLastStartTimeTask].lastStartTime = edfTasks.tasksArray[shortestLastStartTimeTask].lastStartTime
			+ edfTasks.tasksArray[shortestLastStartTimeTask].period;
	#if DEBUG_MODE
		// calculate next absolute deadline of task
		edfTasks.tasksArray[shortestLastStartTimeTask].absoluteDeadline = edfTasks.tasksArray[shortestLastStartTimeTask].absoluteDeadline
				+ edfTasks.tasksArray[shortestLastStartTimeTask].period;
	#endif
	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
	{

	}


}

///* reschedule edf tasks
// * Max execution time with debug mode on: 3 Ticks
// * Max execution time with debug mode off: 2 Ticks
// *  */
//void rescheduleEDF( void )
//{
//	TickType_t currentTick = xTaskGetTickCount();
//	#if DEBUG_MODE
//		// set current Tick to edfTasks struct
//		edfTasks.currentTick = currentTick;
//	#endif
//	for (uint32_t taskCounter = 0u; taskCounter < SIZE_OF_EDF_TASKS_ARRAY; taskCounter ++)
//	{
//		if ( edfTasks.tasksArray[taskCounter].latestStartTime > ( currentTick + edfTasks.tasksArray[taskCounter].relativeDeadline ) )
//		{
//			vTaskPrioritySet( edfTasks.tasksArray[taskCounter].taskHandle, EDF_DISABLED_PRIORITY );
//		}
//		#if DEBUG_MODE
//			else if ( edfTasks.tasksArray[taskCounter].latestStartTime < currentTick )
//			{
//				char buffer[100];
//				timeError++;
//				snprintf(buffer, sizeof(buffer), "ERROR lastStartTime of Task: %s couldn`t reached (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, timeError);
//				debugPrintln(buffer);
//			}
//		#endif
//		else
//		{
//			// check if callCounter of task reach max of uint32_t
//			if (edfTasks.tasksArray[taskCounter].callCounter == UINT32_MAX)
//			{
//				// prevent overflow -> set callCounter to zero
//				edfTasks.tasksArray[taskCounter].callCounter = 0;
//				#if DEBUG_MODE
//					char buffer[100];
//					snprintf(buffer, sizeof(buffer), "CallCounter of Task: %s resettet to 0 (prevent overflow)", edfTasks.tasksArray[taskCounter].taskName );
//					debugPrintln("ERROR in calcShortestDeadline");
//				#endif
//			}
//			else
//			{
//				// increase task call counter
//				edfTasks.tasksArray[taskCounter].callCounter++;
//			}
//			// calculate next latest start time of task
//			edfTasks.tasksArray[taskCounter].latestStartTime = edfTasks.tasksArray[taskCounter].latestStartTime
//					+ edfTasks.tasksArray[taskCounter].period;
//			#if DEBUG_MODE
//				// calculate next absolute deadline of task
//				edfTasks.tasksArray[taskCounter].absoluteDeadline = edfTasks.tasksArray[taskCounter].absoluteDeadline
//						+ edfTasks.tasksArray[taskCounter].period;
//			#endif
//			// find shortest deadline task number
//			TickType_t shortestDeadlineTask = calcShortestDeadline();
//			// set the priority of the next task one higher to get running
//			vTaskPrioritySet( edfTasks.tasksArray[shortestDeadlineTask].taskHandle, EDF_ENABLED_PRIOTIRY);
//			// set task number in edf struct
//			edfTasks.activeTask = shortestDeadlineTask;
//			#if DEBUG_MODE
//				edfTasks.cet = xTaskGetTickCount() - currentTick;
//				if ( edfTasks.cet > edfTasks.wcet )
//				{
//					edfTasks.wcet = edfTasks.cet;
//				}
//			#endif
//			break;
//		}
//	}
//		// force context switch if not happend
//	taskYIELD();
//}

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
	edfTasks.tasksArray[edfTaskNumber].lastStartTime = currentTick + deadline - capacity;
	// status of task creation
	BaseType_t xReturned;
	// create normal freeRTOS task
	xReturned = xTaskCreate( taskCode, taskName, stackDepth , NULL, EDF_DISABLED_PRIORITY, &edfTasks.tasksArray[edfTaskNumber].taskHandle );
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
