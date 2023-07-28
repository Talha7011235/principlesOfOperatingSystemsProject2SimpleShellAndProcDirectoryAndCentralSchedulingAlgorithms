#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Function Prototype.
int runFork();

int main()
{
	// Create a for loop that will call the runFork() Function 3 times.
	for(int iIndex = 0; iIndex < 3; iIndex++)
	{
		// Call the runFork() Function.
		if(runFork(iIndex+1) == 1)
		{
			return 1;
		}
	}
	return 0;
}

// The runFork() Function is called in the main function "int main()" 3 times and prints out the Parent Process IDs and Child Process IDs for
// each process. 
int runFork(int child)
{
        pid_t retVal;

        retVal = fork();
        if(retVal < 0){

                printf("fork() failed\n");
                return 1;
        }
        else if(retVal == 0){

                printf("fork1 retValue == 0 ");
                printf("in child process pid = %d \n", getpid());
                printf("child sleeping ... \n" );
                sleep(5);
                printf(" finished sleeping\n" );
        }
        else{

                printf("parent pid = %d \n", getpid());
                printf("fork1 in parent process waiting for child ...\n");
                wait(NULL);
                printf("Wait() finished in parent process \n");
        }
        return 0;
}
