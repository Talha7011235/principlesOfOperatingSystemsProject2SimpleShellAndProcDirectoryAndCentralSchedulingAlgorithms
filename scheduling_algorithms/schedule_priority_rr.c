#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

struct node *listOfTasks[MAX_PRIORITY + 1];
int currentPriority= MAX_PRIORITY;
struct node *nextTaskNode;

// *********************************************************************************
// First, the Definition of Function void add(char *name, int priority, int burst) *
// that is declared and listed as a Function Prototype in the header               *
// file schedulers.h is that a task must be added to its Priority List.            *
// *********************************************************************************
void add(char *name, int priority, int burst)
{
	Task *tIsForTask = malloc(sizeof(Task));
	// Second, the memory needs to be allocated. Then copy the name of the task.
	tIsForTask->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(tIsForTask->name, name);

	// Third, do linked list implementation for variables "int priority"
	// and "int burst".
	tIsForTask->priority = priority;
	tIsForTask->burst = burst;

	// Call the insert() Function that is defined in the list.c File
	// and is listed as an operation in the header file list.h and insert
	// into the list of tasks that is represented by the variable "listOfTasks".
	insert(&listOfTasks[priority], tIsForTask);
}

// **********************************************************************************************************************************************
// The pickNextTask() Function will choose the next task to execute as a result of scheduling tasks in order of Priority along with             *
// using Round-Robin** RR Scheduling for tasks with equal Priority by using the Priority* with Round-Robin** Scheduling Algorithm. Furthermore, *
// in order for the pickNextTask() Function to work properly, the *listOfTasks should not be empty.                                             *
// **********************************************************************************************************************************************
Task *pickNextTask()
{
	printf("\n1. Select the next task in the list to run.\n");
	// Determine the conditions for if there are no more tasks left at the Current Priority.
	if(listOfTasks[currentPriority] == NULL)
	{
		printf("\ta.) There are no tasks left at this priority. Therefore, find the next priority with tasks.\n");
		currentPriority--;

		char c = 'b';
		// Search for a Priority to run starting at the Current Priority which defaults to the Maximum Priority.
		for(int iIndex = currentPriority; iIndex > 0; --iIndex)
		{
			if(listOfTasks[iIndex] != NULL)
			{
				currentPriority = iIndex;
				nextTaskNode = listOfTasks[iIndex];
				break;
			}
			printf("\t%c.) Priority %d does not have tasks.\n", c++, iIndex);
		}

		printf("\t%c.) Priority %d has tasks.\n", c, currentPriority);
	}

	Task *returnPriorityWithRoundRobinTask = nextTaskNode->task;

	nextTaskNode = nextTaskNode->next;
	if(nextTaskNode == NULL)
	{
		nextTaskNode = listOfTasks[currentPriority];
	}
	return returnPriorityWithRoundRobinTask;
}

// *************************************************************************************************************************************
// Define the void schedule() Function that is included in the header file schedulers.h and is called in the driver.c file in order to *
// invoke the Process Scheduler.                                                                                                       *
// *************************************************************************************************************************************
void schedule()
{
	printf("The Scheduling Algorithm Priority* with Round-Robin** schedules tasks in order of Priority and uses Round-Robin Scheduling\n");
	printf("for tasks with equal priority. In other words, the Scheduling Algorithm Priority* with Round-Robin** Scheduling attempts to\n");
	printf("ensure that all of the tasks of the same priority get equal treatment with the Processor by using the same Round Robin\n");
	printf("switching but organizing the tasks in a collection of Priority Lists.\n");
	printf("----------------------------------------------------------------------------------------------------------------------------\n");
	nextTaskNode = listOfTasks[currentPriority];

	// Create a while loop to test the conditions of what happen while the Priority is greater than 1 or currently there are no tasks left
	// to run.
	while(currentPriority > 1 || listOfTasks[currentPriority])
	{
		Task *tIsForTask = pickNextTask();
		int slice = QUANTUM < tIsForTask->burst ? QUANTUM: tIsForTask->burst;
		printf("\n2. The Scheduler will run task %s for a CPU burst of %d milliseconds.\n", tIsForTask->name, slice);
		run(tIsForTask, slice);

		printf("\n3. Reduce the burst of the task by the quantum.\n");
		tIsForTask->burst -= slice;

		printf("\n4. Then, check if the task is complete and check if the task needs to be removed from the list.\n");
		if(tIsForTask->burst < 1)
		{
			printf("\n5. Remove, that is delete, the completed task.\n");
			delete(&listOfTasks[currentPriority], tIsForTask);

			// Free the task information in order to prevent a memory leak or memory leaks.
			free(tIsForTask->name);
			free(tIsForTask);
		}
		printf("\n--------------------------------------------------------------------------------------------------------------------");
		printf("--------\n");
	}
}
