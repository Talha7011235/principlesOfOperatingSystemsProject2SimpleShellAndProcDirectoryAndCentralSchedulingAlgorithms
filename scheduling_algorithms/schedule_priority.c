#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

struct node *listOfTasks = NULL;

// *********************************************************************************
// First, the Definition of Function void add(char *name, int priority, int burst) *
// that is declared and listed as a Function Prototype in the header               *
// file schedulers.h is that a task must be added to its Priority List.            *
// *********************************************************************************
void add(char *name, int priority, int burst)
{
	Task *tIsForTask = malloc(sizeof(Task));
	// Second, the memory needs to be allocated. Then, copy the name of the
	// task.
	tIsForTask->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(tIsForTask->name, name);

	// Third, do linked list implementation for variables "int priority"
	// and "int burst".
	tIsForTask->priority = priority;
	tIsForTask->burst = burst;

	// Call the insert() Function that is defined in the list.c File
	// and is listed as an operation in the header file list.h and insert
	// into the list of tasks that is represented by the variable "listOfTasks".
	insert(&listOfTasks,tIsForTask);

}

// *************************************************************************************************************
// The pickNextTask() Function will choose the next task to execute that has the Highest Priority by using the *
// Scheduling Algorithm Priority *Scheduling. Furthemore, in order for the pickNextTask() Function to work     *
// properly, the *listOfTasks should not be empty.                                                             *
// *************************************************************************************************************
Task *pickNextTask()
{
	Task *taskWithHighestPriority = listOfTasks->task;
	struct node *nForNode = listOfTasks;
	printf("\n1. Determine the next task priority descending in terms of computing and comparing the next task that has the\n");
	printf("   highest numeric value that indicates the highest relative priority.\n");
	printf("task %s selected\n", nForNode->task->name);
	while(nForNode)
	{
		if(nForNode->task->priority > taskWithHighestPriority->priority)
		{
			printf("task %s[%d] superseded by task %s[%d]\n", taskWithHighestPriority->name, taskWithHighestPriority->priority, nForNode->task->name, nForNode->task->priority);
			taskWithHighestPriority = nForNode->task;
		}
		nForNode = nForNode->next;
	}
	return taskWithHighestPriority;
}

// **************************************************************************************
// Define the void schedule() Function that is included in the header file schedulers.h *
// and is called in the driver.c file in order to invoke the Process Scheduler.         *
// **************************************************************************************
void schedule()
{
	printf("The Scheduling Algorithm Priority* scheduling uses the priority variable on every task to find the next task to run\n");
	printf("in a descending manner by displaying and listing the 'Running tasks' from the highest relative priority of the\n");
	printf("highest numeric value to the  lowest relative priority of the lowest numeric value in the schedule.\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	while(listOfTasks)
	{
		Task *tIsForTask = pickNextTask();

		printf("\n2. The Scheduler will run task %s.\n", tIsForTask->name);
		run(tIsForTask, tIsForTask->burst);

		printf("\n3. Remove, that is delete, the completed task.\n\n------------------------------------------------------------------");
		printf("--------------------------------------------------\n");
		delete(&listOfTasks, tIsForTask);
	}
}
