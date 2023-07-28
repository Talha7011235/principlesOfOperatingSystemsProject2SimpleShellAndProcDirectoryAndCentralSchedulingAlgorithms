#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"
#define BUFFER_LEN 1024

// Function Prototypes.
int loopForUserPrompt();
int returnIfStringIsANumber(char* tForText);
char* getCommandForUser();
char** parseCommand(char* userInput, int nNumberOfTokens);
void procExecution(char** tIsForTokens);
void procCD(char** tIsForTokens);
void commandForExecute(char** tIsForTokens);

int main(int argc, char *argv[])
{
	// In order to make sure that no command-line arguments are passed, the
	// Function "int main(int argc, char *argv[])" checks the number of
	// arguments passed. In other words, the Function "int main(int argc,
	// char *argv[]) exits the shell with a print statement, that is a message,
	// to stderror and returns 1 as the value if the number of 
	// arguments is greater than 1.
	if (argc > 1)
	{
		fprintf(stderr, "Shell program executes and therefore the shell takes no command-line arguments.\n");
		return 1;
	}
	else
	{
		printf("%s\n", argv[0]);
		return loopForUserPrompt();
	}
	return 0;
}

// *********************************************************************************
// The Function returnIfStringIsANumber() will return if the string is a           * 
// number. In addition, for the Function returnIfStringIsANumber(), the number has *
// to be an integer and this can include a negative number.                        *
// *********************************************************************************
int returnIfStringIsANumber(char *str)
{
	// Check if the sign of the number is negative.
	char* tForText = str;
	if (*tForText != '-' && !isdigit(*tForText))
	{
		return 0;
	}
	tForText++;

	// Check the whole text.
	while (*tForText)
	{
		if (!isdigit(*tForText))
		{
			return 0;
		}
		tForText++;
	}
	return 1;
}

int loopForUserPrompt()
{
	printf("This is the Simple Shell\n");

	while (1)
	{
		printf("$ ");
		// Get the User Input. 
		char * userInput = getCommandForUser();

		if (userInput[0] == '\0')
		{
			free(userInput);
			continue;
		}

		char *dummyVariable = unescape(userInput, stderr);
		if (dummyVariable == NULL)
		{
			free(userInput);
			continue;
		}
		free(userInput);
		userInput = dummyVariable;

		char* checkCurrentQuote = userInput;
		int quoteCounterIsSingle = 0;
		int quoteCounterIsDouble = 0;

		while (*checkCurrentQuote != '\0')
		{
			if (*checkCurrentQuote == '\'')
			{
				quoteCounterIsSingle++;
			}
			if (*checkCurrentQuote == '"')
			{
				quoteCounterIsDouble++;
			}
			checkCurrentQuote++;
		};
		if (quoteCounterIsSingle % 2 == 1 || quoteCounterIsDouble % 2 == 1)
		{
			printf("Sorry! The command is Invalid.\n");
			free(userInput);
			continue;
		}

		// First, add 1 to the Number of Tokens that is represented by the
		// variable "nNumberOfTokens" due to the fact that the Number of
		// of Tokens is greater than its space by one. Then, at the end
		// of the array, add 1 to the "NULL" token.
		int nNumberOfTokens = count_spaces(userInput) + 2;
		char ** tIsForTokens = parseCommand(userInput, nNumberOfTokens);

		// for(int i = 0; i < nNumberOfTokens; ++i) {
		// 	printf("%d: %s\n", i, tIsForTokens[i]);
		// }
		// Second, do the execute command.
		if (tIsForTokens[0] == NULL)
		{
			printf("Sorry! The command is Invalid.\n");
			free(tIsForTokens);
			free(userInput);
			continue;
		}
		// Third, create a built-in exit command for the shell.
		else if (strncmp(tIsForTokens[0], "exit", 10) == 0)
		{
			if (nNumberOfTokens == 2 || (nNumberOfTokens == 3 && returnIfStringIsANumber(tIsForTokens[1])))
			{
				int argument = 0;
				if (nNumberOfTokens == 3)
				{
					argument = atoi(tIsForTokens[1]);
				}
				free(tIsForTokens);
				free(userInput);

				return argument;
			}
			else
			{
				fprintf(stderr, "Sorry! The argument for exit is Invalid!\n");
			}
		}
		// Next, read information from the /proc filesystem.
		else if (strncmp(tIsForTokens[0], "proc", 10) == 0)
		{
			if (nNumberOfTokens == 3)
			{
				procExecution(tIsForTokens);
			}
			else
			{
				fprintf(stderr, "Sorry! The argument for proc is Invalid!\n");
			}
		}
		// Then, add the "cd" command in order to change the working directory by calling the Function void procCD(char** tIsForTokens).
		else if (strncmp(tIsForTokens[0], "cd", 10) == 0)
		{
			if (nNumberOfTokens == 3)
			{
				procCD(tIsForTokens);
			}
			else
			{
				fprintf(stderr, "Sorry! The argument for cd is Invalid!\n");
			}
		}
		else
		{
			commandForExecute(tIsForTokens);
		}

		free(tIsForTokens);
		free(userInput);
	}
}

// *******************************************************************************
// First, the Function getCommandForUser() will get the undetermined size of the *
// User Input that is represented by the variable "userInput" and then the       *
// Function getCommandForUser() returns to the Function loopForUserPrompt().     *
// *******************************************************************************

char* getCommandForUser()
{
	size_t sizeOfDefault = 200;
	char * userInput = malloc(sizeOfDefault * sizeof(char));

	// Use getline() Function to prevent valgrind errors that includes memory errors and memory leaks.
	int bufferCount = getline(&userInput, &sizeOfDefault, stdin);

	// Remove the newline character from the end of the buffer.
	userInput[bufferCount-1] = '\0';

	return userInput;
}

char** parseCommand(char* userInput, int nNumberOfTokens)
{
	char** tIsForTokens = malloc(nNumberOfTokens * sizeof(char*));
	char* tempVariable = strtok(userInput, " ");

	int i = 0;
	// Initialize all the values in tokens.
	for(i = 0; i < nNumberOfTokens; ++i) {
		tIsForTokens[i] = NULL;
	}

	i = 0;
	while (tempVariable != NULL)
	{
		tIsForTokens[i] = tempVariable;
		tempVariable = strtok(NULL, " ");
		i++; // iIndex
	}
	return tIsForTokens;
}

void procExecution(char** tIsForTokens)
{
	char *setDefaultPathForFile = "/proc/";
	int sizeOfDefault = strlen(tIsForTokens[1]) + strlen(setDefaultPathForFile) + 1;
	char* filePath = malloc(sizeOfDefault * sizeof(char));
	// Ensure that strncat has a Null Terminator to work from.
	filePath[0] = '\0';
	strncat(filePath, setDefaultPathForFile, sizeOfDefault);
	strncat(filePath, tIsForTokens[1], sizeOfDefault);

	FILE *buildFileToReadPointer = fopen(filePath, "r");
	char readLine;

	if (buildFileToReadPointer == NULL)
	{
		fprintf(stderr, "Sorry, the file is not found!\n");
	}
	else
	{
		readLine = fgetc(buildFileToReadPointer);
		while (readLine != EOF)
		{
			printf("%c", readLine);
			readLine = fgetc(buildFileToReadPointer);
		}
		printf("\n");
		fclose(buildFileToReadPointer);
	}
	free(filePath);
}

void procCD(char** tIsForTokens)
{
	chdir(tIsForTokens[1]);
}

// ************************************************************************
// The Function commandForExecute() implements the parsed command         *
// in the event that the commands are not "proc". In addition, the        *
// Function commandForExecute() implements the parsed command             *
// in the event that the commands are not "exit". Therefore, the          *
// Function commandForExecute() forks a process and inside the child      *
// process, the Function commandForExecute() performs the parsed command. *
// ************************************************************************ 
void commandForExecute(char** tIsForTokens)
{
	char* inputPathOfCommand = "/bin/";
	int sIsForSize = strlen(tIsForTokens[0]) + strlen(inputPathOfCommand) + 1;
	char* cIsForCommand = malloc(sIsForSize * sizeof(char));

	// The strncat() Function looks for the Null Terminator to append and if the Null Terminator does not exist, then 
	// it has a valgrind error.
	cIsForCommand[0] = '\0';
	if (tIsForTokens[0][0] != '/')
	{
		strncat(cIsForCommand, inputPathOfCommand, sIsForSize);
	}
	strncat(cIsForCommand, tIsForTokens[0], sIsForSize);

	int pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Sorry, you cannot fork!\n");
	}
	else if (pid == 0)
	{
		// Conditions for Child Process.
		execv(cIsForCommand, tIsForTokens);

		fprintf(stderr, "Sorry, the command is Invalid!\n");
		exit(1);
	}
	else
	{
		// Conditions for Parent Process.
		wait(NULL);
		free(cIsForCommand);
	}
}

/*void shellCommand()
{

	// Get the command line.
	char commandLine[BUFFER_LEN];

	// User Command
	char* argv[100];

	// The path needs to be set at the bin.
	char* path = "/bin/";

	// Entire File Path
	char entireFilePath[20];

	// Create an Argument Count Variable.
	int argc;

	while (1)
	{
		//Create a Print Statement for the Shell Prompt.
		printf("$ ");

		// First, get the command. Then, place the command in the command
		// line that is represented by the variable "int commandLine".
		if (!fgets(commandLine, BUFFER_LEN, stdin))
		{
			// If the user presses the computer keys "Ctrl" + "D" on
			// his or her computer keyboard, then break.
			break;
		}

		// Check if the command is the exit command.
		if (strcmp(commandLine, "exit\n") == 0)
		{
			printf("Sorry! The command is Invalid!\n");
			break;
		}

		// The command must be splitted into separate strings.
		char *tIsForToken;
		tIsForToken = strtok(commandLine, " ");
		int i = 0; 
		while (tIsForToken != NULL)
		{
			argv[i] = tIsForToken;
			tIsForToken = strtok(NULL, " ");
			i++;
		}

		// Set last value to NULL for execvp.
		argv[i] = NULL; 

		// Get Argument Count.
		argc = i;
		for (i = 0; i < argc; i++)
		{
			// Print command/arguments.
			// printf("%s\n", argv[iIndex]);
		}

		// Copy /bin/ to the entire file path.
		strcpy(entireFilePath, path);
		// Add the entire file path represented by the variable "entireFilePath" to the "path". 
		strcat(entireFilePath, argv[0]);

	}

}*/
