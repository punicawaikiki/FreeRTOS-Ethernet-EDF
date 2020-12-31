/* description */

#include "edf_tasks.h"
#include <user_variables.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "helper_functions.h"
#include "stdio.h"

edfTasks_s edfTasks;


/* reschedule edf tasks
 * Max execution time with debug mode on: 3 Ticks
 * Max execution time with debug mode off: 2 Ticks
 *  */
void rescheduleEDF( void )
{
	// get current tick of system
	TickType_t currentTick = xTaskGetTickCount();

//	deleteEDFTask("task1");


	// init shortest lastStartTime buffer variable
	TickType_t shortestLastStartTimeTask = -1;
	// buffer for initialization of shortest lastStartTime
	uint32_t initTaskNumber = 0;
	#if DEBUG_MODE
		// set current Tick to edfTasks struct
		edfTasks.currentTick = currentTick;
	#endif
	// iterate over all tasks and get shortest lastStartTime task
	for (uint32_t taskCounter = 0u; taskCounter < edfTasks.numberOfEDFTasks; taskCounter ++)
	{
		// check tasks is to far away for execution
		if ( edfTasks.tasksArray[taskCounter].lastStartTime > ( currentTick + edfTasks.tasksArray[taskCounter].relativeDeadline ) )
		{
			// increase initial task number
			initTaskNumber++;
		}
		// deadline could not reached, restart Task (if DEBUG_MODE is on print ERROR)
		else if( edfTasks.tasksArray[taskCounter].lastStartTime < currentTick)
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
				snprintf(buffer, sizeof(buffer), "ERROR deadline of task: %s missed (Error counter: %lu)", edfTasks.tasksArray[taskCounter].taskName, edfTasks.tasksArray[taskCounter].deadlineErrorCounter);
				debugPrintln(buffer);
			#endif
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
	}
	// next task should be idle task
	if ( shortestLastStartTimeTask == -1 )
	{
		// if current task is not idle task, priority should set back to EDF_DISABLED_PRIORITY
		if( xTaskGetCurrentTaskHandle() != edfTasks.idleTask )
		{
			vTaskPrioritySet( NULL, EDF_DISABLED_PRIORITY);
		}
	}
	// set parameters and priority for next normal task
	else
	{
		// check if callCounter of task reach max of uint32_t
		if (edfTasks.tasksArray[shortestLastStartTimeTask].callCounter == UINT32_MAX)
		{
			// prevent overflow -> set callCounter to zero
			edfTasks.tasksArray[shortestLastStartTimeTask].callCounter = 0;
			#if DEBUG_MODE
				char buffer[100];
				snprintf(buffer, sizeof(buffer), "CallCounter of Task: %s reset to 0 (prevent overflow)", edfTasks.tasksArray[shortestLastStartTimeTask].taskName );
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
		// set priority to highest value -> no context switch while scheduling
		vTaskPrioritySet( NULL, EDF_SCHEDULE_PRIORITY);
		// set priority of choosen task to EDF_ENABLED_PRIOTIRY
		vTaskPrioritySet( edfTasks.tasksArray[shortestLastStartTimeTask].taskHandle, EDF_ENABLED_PRIOTIRY);
		// set current normal task to EDF_DISABLED_PRIORITY and idle task to EDF_IDLE_PRIORITY
		if( xTaskGetCurrentTaskHandle() == edfTasks.idleTask )
		{
			vTaskPrioritySet( NULL, EDF_IDLE_PRIORITY);
		}
		else
		{
			vTaskPrioritySet( NULL, EDF_DISABLED_PRIORITY);
		}
	}
	// if context switch not happened, do it now
	taskYIELD();
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
	// suspend task till freeRTOS idleTask are called
		vTaskSuspend( edfTasks.tasksArray[edfTaskNumber].taskHandle );
	// set task name
	edfTasks.tasksArray[edfTaskNumber].taskName = taskName;
	// set capacity of task
	edfTasks.tasksArray[edfTaskNumber].wcet = capacity;
	// set period of task
	edfTasks.tasksArray[edfTaskNumber].period = period;
	// increment number of tasks
	edfTasks.numberOfEDFTasks++;
	// return pdTrue if task creation was successful, pdFalse when not
	return xReturned;
}

BaseType_t deleteEDFTask( const char* taskName)
{
	// flag to control task deletion
	BaseType_t taskDeleted = pdFALSE;
	if( xTaskGetCurrentTaskHandle() != edfTasks.idleTask )
	{
		vTaskPrioritySet( NULL, EDF_IDLE_PRIORITY);
	}
	// iterate over all tasks
	for (uint32_t taskCounter = 0u; taskCounter < edfTasks.numberOfEDFTasks; taskCounter ++)
	{
		// compare tasks names
		if( strcmp(taskName, edfTasks.tasksArray[taskCounter].taskName) == 0 )
		{
			// delete task
			vTaskDelete( edfTasks.tasksArray[taskCounter].taskHandle );
//			prvCheckTasksWaitingTermination();
			taskDeleted = pdTRUE;
//			edfTasks.tasksArray[taskCounter] edfTaskStruct;
		}
	}
	// if task deletion was successful return pdTRUE, else pdFALSE
	if( taskDeleted == pdTRUE)
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	};
}

//	this hook is called if no task is in ready state
void vApplicationIdleHook( void )
{
	// set freeRTOS idle task priority to EDF_IDLE_PRIORITY once
	if (edfTasks.numberOfEDFTasks > 0)
	{
		// change priority of freeRTOS idleTask
		if( edfTasks.idleTaskCreated == pdFALSE)
		{
			// get freeRTOS idleTask taskhandle
			edfTasks.idleTask = xTaskGetIdleTaskHandle();
			// set priority of freeRTOS idleTask to EDF_IDLE_PRIORITY
			vTaskPrioritySet( edfTasks.idleTask, EDF_IDLE_PRIORITY );
			// set flag
			edfTasks.idleTaskCreated = pdTRUE;
		}
		// iterate over all tasks and resume them if not done yet
		for (uint32_t taskCounter = 0u; taskCounter < edfTasks.numberOfEDFTasks; taskCounter ++)
		{
			if( edfTasks.tasksArray[taskCounter].taskCreated == pdFALSE )
			{
				// resume/start task for edf scheduling
				vTaskResume( edfTasks.tasksArray[taskCounter].taskHandle );
				// flag signals task creation
				edfTasks.tasksArray[taskCounter].taskCreated = pdTRUE;
			}
		}
		// edf scheduling
		rescheduleEDF();
	}
}
