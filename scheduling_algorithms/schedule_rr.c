#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

struct node *listOfTasks = NULL;
struct node *nextTaskNode;

// *********************************************************************************
// First, the Definition of Function void add(char *name, int priority, int burst) * 
// that is declared and listed as a Function Prototype in the header               *
// file schedulers.h is to add a task to the list.                                 *
// *********************************************************************************
void add(char *name, int priority, int burst)
{
	Task *tIsForTask = malloc(sizeof(Task));
	// Second the memory needs to be allocated. Then, copy the name of the task.
	tIsForTask->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(tIsForTask->name, name);

	// Third, do linked list implementation for the variables "int priority"
	// and "int burst". 
	tIsForTask->priority = priority;
	tIsForTask->burst = burst; 

	// Call the insert() Function that is defined in the list.c File
	// and is listed as an operation in the header file list.h and insert
	// into the list of tasks that is represented by the variable "listOfTasks".
	insert(&listOfTasks, tIsForTask);  
}

// ***********************************************************************************************************************************************
// The pickNextTask() Function will choose the next task to execute by using the Scheduling Algorithm Round-Robin RR Scheduling. Furthermore, in *
// order for the pickNextTask() Function to work properly, the *listOfTasks should not be empty.                                                 *
// ***********************************************************************************************************************************************
Task *pickNextTask()
{
	Task *returnNode = nextTaskNode->task;

	printf("\n1. Select the next task in the list to run.\n");
	nextTaskNode = nextTaskNode->next;
	if(nextTaskNode == NULL)
	{
		nextTaskNode = listOfTasks;
	}

	return returnNode;

}

// *************************************************************************************************************************************
// Define the void schedule() Function that is included in the header file schedulers.h and is called in the driver.c file in order to *
// invoke the Process Scheduler.                                                                                                       *
// *************************************************************************************************************************************
void schedule()
{
	printf("In the Scheduling Algorithm Round-Robin** RR Scheduling, each task runs for a time quantum or for the remainder of\n");
	printf("its Central Processing Unit CPU Burst. In other words, the Scheduling Algorithm Round-Robin** RR attempts to ensure\n");
	printf("that all of the tasks get equal treatment with the Processor by only running each task for a short amount of time\n");
	printf("and then switching to the next task.\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");

	nextTaskNode = listOfTasks;
	while(listOfTasks)
	{
		Task *tIsForTask = pickNextTask();
		// Run this task in order to get the amount of time.
		int slice = QUANTUM < tIsForTask->burst ? QUANTUM:tIsForTask->burst;
		printf("\n2. The Scheduler will run the task %s for a CPU burst of %d milliseconds.\n", tIsForTask->name, slice);
		run(tIsForTask, slice);

		printf("\n3. Reduce the burst of the task by the quantum.\n");
		//Remove the amount of time in the slice that is represented by the variable "int slice".
		tIsForTask->burst -= slice;

		printf("\n4. Then, check if the task is complete and check if the task needs to be removed from the list.\n");
		// If the task is done, then remove the task from the list.
		if(tIsForTask->burst < 1)
		{
			printf("\n5. Remove, that is delete, the completed task.\n");
			delete(&listOfTasks, tIsForTask);

			// Free the task information in order to prevent a memory leak or memory leaks. 
			free(tIsForTask->name);
			free(tIsForTask);
		}
		printf("\n--------------------------------------------------------------------------------------------------------------------\n");
	}
}
