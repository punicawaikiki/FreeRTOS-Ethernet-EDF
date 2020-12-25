/* This File implement EDF Scheduling */

#ifndef __EDF_SCHEDULER_H
#define __EDF_SCHEDULER_H

#include "FreeRTOS.h"
#include "task.h"

/* config parameters for EDF scheduler */
#define EDF_SCHEDULER_PRIORITY			( configMAX_PRIORITIES - 1 )
#define EDF_SCHEDULER_STACK_SIZE		( 1000us )
#define EDF_SCHEDULER_TASK_PERIOS		( 100us )
//#define portEND_SWITCHING_ISR( xSwitchRequired )

#endif /* __EDF_SCHEDULER_H */
