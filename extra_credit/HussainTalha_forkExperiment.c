#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	// Variable to store the depth.
	int depth = 0;

	// Variable to store the last depth value to loop on.
	int maximumForLastDepthValueToLoopOn = 4;

	if(argc > 1)
	{
		maximumForLastDepthValueToLoopOn = atoi(argv[1]);
		// Create a condition for if the maximum for the last depth value to loop on is less than 0, then it cannot loop without
		// at least one iteration.
		if(maximumForLastDepthValueToLoopOn < 0)
		{
			 maximumForLastDepthValueToLoopOn = 1;
		}

		// Create a condition for if the maximum for the last depth value to loop on is greater than 8, then it
		// will max out at 256 Processes.
		if(maximumForLastDepthValueToLoopOn > 8)
		{
			maximumForLastDepthValueToLoopOn = 8;
		}
	}

	// Create while loop to test the condition of what happens when the depth limit has not yet been reached.
	while(depth < maximumForLastDepthValueToLoopOn)
	{
		// Print out the Depth and Process ID.
		printf("Depth: %d (%d)\n\n", depth, getpid());

		// Increase the depth.
		depth++;

		// Perform the fork.
		pid_t retVal = fork();

		// If the fork fails, then return. If the fork does not fail, then loop to the next fork.
		if(retVal < 0)
		{
			printf("fork() failed for pid: %d\n", getpid());
			return 1;
		} 
	} 

	// Wait for the children specifically the Process ID of each Child Process to complete.
	wait(NULL);
	return 0;
}
