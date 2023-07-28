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
	// Second, the memory needs to be allocated. Then,copy the name of the task.
	tIsForTask->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(tIsForTask->name,name);

	// Third, do linked list implementation for variables "int priority"
	// and "int burst".
	tIsForTask->priority = priority;
	tIsForTask->burst = burst;

	// Call the insert() Function that is defined in the lsit.c FIle
	// and is listed as an operation in the header file list.h and insert
	// into the list of tasks that is represented by the variable "listOfTasks".
	insert(&listOfTasks, tIsForTask);
}

// *********************************************************************************
// The pickNextTask() Function will choose the next task to execute by using the   *
// Shortest-job-first SJF Scheduling Algorithm. Furthermore, in order for the      *
// pickNextTask() Function to work properly, the *listOfTasks should not be empty. *
// *********************************************************************************
Task *pickNextTask()
{
	Task *shortestJobFirst = listOfTasks->task;
	struct node *nextTaskNode= listOfTasks;
	printf("\n1. Determine the next task by burst ascending in terms of computing and comparing the next task that has the lowest burst value.\n");
	printf("task %s selected\n", nextTaskNode->task->name);
	while(nextTaskNode)
	{
		if(nextTaskNode->task->burst < shortestJobFirst->burst)
		{
			printf("task %s[%d] superseded by task %s[%d]\n", shortestJobFirst->name, shortestJobFirst->burst, nextTaskNode->task->name, nextTaskNode->task->burst);
			shortestJobFirst = nextTaskNode->task;
		}
		nextTaskNode = nextTaskNode->next;
	}
	return shortestJobFirst;
}

// **************************************************************************************
// Define the void schedule() Function that is included in the header file schedulers.h *
// and is called in the driver.c file in order to invoke the Process Scheduler.         *
// **************************************************************************************
void schedule()
{
	printf("First, the Shortest-job-first SJF Scheduling Algorithm scans all tasks for the lowest burst value. Then, the\n");
	printf("Shortest-job-first SJF Scheduling Algorithm selects the task that has the lowest burst value to run in the schedule. In other\n");
	printf("words, the Shortest-job-first SJF Scheduling Algorithm schedules tasks in order of the length of the tasks' next\n");
	printf("Central Processing Unit CPU Burst.\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------");
	printf("--\n");
	while(listOfTasks)
	{
		Task *tIsForTask = pickNextTask();

		printf("\n2. Scheduler will run the task %s.\n", tIsForTask->name);
		run(tIsForTask, tIsForTask->burst);

		printf("\n3. Remove, that is delete, the completed task.\n\n-------------------------------------------------------------------");
		printf("--------------------------------------------------------------\n");
		delete(&listOfTasks, tIsForTask);

		// Free the task information in order to prevent a memory leak or memory leaks.
		free(tIsForTask->name);
		free(tIsForTask);
	}
}
