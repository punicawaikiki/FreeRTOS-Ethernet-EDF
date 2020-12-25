/* This File implement EDF Scheduling */
/* Inspired by Robin Kase:
 * https://github.com/RobinK2/ESFree
 */

/* includes */
#include "edf_scheduler.h"
#include "helper_functions.h"

/* module globals */

static List_t tcbAll;				// List of all tasks
static List_t* pTCBAll = NULL;
static List_t tcbOverflowedList;	// List of all overflowed tasks
static List_t* pTCBOverflowedList = NULL;

static void edfSchedulerInit( void );
static void edfSchedulerStart( void );
static void edfUpdateTaskPriorites( void );
static void edfSchedulerTask( void );
static void swapLists(List_t** tcbList1, List_t** tcbList2);


/* create modified FreeRTOS Task Control Block (TCB) with EDF Components */
typedef struct modfiedTCB
{
	/* FreeRTOS TCB Contents */
	TaskFunction_t taskCode;     		// Pointer to the task entry function
	const char* taskName; 				// A descriptive name for the task
	configSTACK_DEPTH_TYPE stackDepth;  // The number of words (not bytes!) to allocate for use as the task’s stack
	void* taskParameters; 				// A value that will passed into the created task as the task’s parameter
	UBaseType_t priority;				// The priority at which the created task will execute
	TaskHandle_t* createdTaskHandle;    // Used to pass a handle to the created task out of the xTaskCreate() function
	/* parameters of EDF */
	TickType_t releaseTime;    			// release time of the task
	TickType_t capacity;   				// capacity or worst-case computation time
	TickType_t relativeDeadline; 		// task relative deadline, i.e. the maximum acceptable delay for its processing
	TickType_t absoluteDeadline; 		// task absolute deadline
	TickType_t period; 					// task period
	/* variables for scheduling EDF */
	TickType_t lastRunningTime; 		// timestamp when the task was last run
	TickType_t currentExecutionTime;    // current execution time
	BaseType_t jobFinished;				// true if task is finished
	/* sorted List reference to TCB*/
	ListItem_t TCBListItem; 			// reference to tcb
}edfTCB;


static void swapLists(List_t** tcbList1, List_t** tcbList2)
{
	// generate a buffer list
	List_t* bufferList;
	// copy content of tcbList1 into bufferList
	bufferList = *tcbList1;
	// copy content of tcbList2 into tcbList2
	*tcbList1 = *tcbList2;
	// copy content of buffer list into tcbList2
	*tcbList2 = bufferList;
}


/* updating priorities of all tasks */
static void edfUpdateTaskPriorites( void )
{
	edfTCB* tcb;
	ListItem_t* currentTCBListItem;
	ListItem_t* tcbListItemTemp;
	// check if no tasks in tcbAll and there is any task in the overflowed List
	if( listLIST_IS_EMPTY( pTCBAll ) && !listLIST_IS_EMPTY( pTCBOverflowedList ))
	{
		swapLists( &pTCBAll, &pTCBOverflowedList );
	}
	// get head entry of tcbAll list
	currentTCBListItem = listGET_HEAD_ENTRY( pTCBAll );
	// get endmarker of tcbAll List
	const ListItem_t* tcbListEndMarker = listGET_END_MARKER( pTCBAll );

}


static void edfSchedulerTask( void )
{

}


static void edfSchedulerInit( void )
{
	vListInitialise( &tcbAll );			// init EDF TCB list
	pTCBAll = &tcbAll;
}

static void edfSchedulerStart( void )
{
	// init priorities of all perodic tasks
	edfTCB* tcb;
	/*
	 * set the highest priority of the EDF choosen task one priority lower than the scheduler.
	 * first task of list gets highest priority of tasks, and decrement for every item in list
	 */
	UBaseType_t priorityDecrementCounter = EDF_SCHEDULER_PRIORITY - 1;
	// get head entry of tcbAll list
	ListItem_t* currentTCBListItem = listGET_HEAD_ENTRY( pTCBAll );
	// get endmarker of tcbAll List
	const ListItem_t* tcbListEndMarker = listGET_END_MARKER( pTCBAll );
	// priorityDecrementCounteriterate over all tasks in list
	while( currentTCBListItem != tcbListEndMarker )
	{
		// get task from list
		tcb = listGET_LIST_ITEM_OWNER( currentTCBListItem );
		// set priority for task
		tcb->priority = priorityDecrementCounter;
		// decrement priority of variable
		priorityDecrementCounter--;
		// get next task of list
		currentTCBListItem = listGET_NEXT( currentTCBListItem );
	}
	// create EDF Scheduler task
//	xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask)


}
