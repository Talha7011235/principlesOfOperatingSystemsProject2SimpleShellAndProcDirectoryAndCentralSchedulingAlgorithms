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
// file schedulers.h is to add a task to the list.                                 *
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
	// into the list of tasks that is represented by the variable "listofTasks".
	insert(&listOfTasks,tIsForTask);
}

// *******************************************************************************
// The pickNextTask() Function will choose the next task to execute by using the *
// First-come, First-served FCFS Scheduling Algorithm. Furthermore, in order     *
// for the pickNextTask() Function to work properly, the *listOfTasks should     *
// not be empty.                                                                 *
// *******************************************************************************
Task *pickNextTask()
{
	struct node *finalNode = listOfTasks;
	printf("\n1. Select the earliest task to run.\n");
	while(finalNode->next != NULL)
	{
		finalNode= finalNode->next;
	}
	return finalNode->task;
}

// **************************************************************************************
// Define the void schedule() Function that is included in the header file schedulers.h *
// and is called in the driver.c file in order to invoke the Process Scheduler.         *
// **************************************************************************************
void schedule()
{
	printf("The First-come, First-served FCFS Scheduling Algorithm is an uncomplicated schedule system that runs the earliest task\n");
	printf("to be scheduled in each iteration. In other words, the First-come, First-served FCFS Scheduling Algorithm schedules tasks\n");
	printf("in the order in which the tasks request the Central Processing Unit CPU.\n");
	printf("--------------------------------------------------------------------------------------------------------------------------\n");
	while(listOfTasks)
	{
		Task *tIsForTask = pickNextTask();

		printf("\n2. The Scheduler will run task %s.\n", tIsForTask->name);
		run(tIsForTask,tIsForTask->burst);

		printf("\n3. Remove, that is delete, the completed task.\n\n------------------------------------------------------------------");
		printf("--------------------------------------------------------\n");
		delete(&listOfTasks,tIsForTask);

		// Free the task information in order to prevent a memory leak or memory leaks.
		free(tIsForTask->name);
		free(tIsForTask);
	}
}

