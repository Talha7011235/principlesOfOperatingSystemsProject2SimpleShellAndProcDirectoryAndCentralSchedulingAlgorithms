# Simple Shell

A simple shell program for Project 2 Simple Shell and `/proc` Directory and Central Processing Unit CPU Scheduling Algorithms.

## Installation

Unzip principlesOfOperatingSystemsProject2SimpleShellAndProcDirectoryAndSchedulingAlgorithms.zip/ file by extracting all files in order to get into the "simple_shell" directory.

## Usage

Open VirtualBox Debian Terminal, first enter the command "make" and then type the command 'simple_shell' in order to run `./simple_shell` and
build the simple_shell.c executable file.  

## Project Requirements

### Part 1

1. To ensure the shell takes no arguments I put in an `argc` check to let the user know that they can no use arguments with the program. If there
   are no arguments it continues into the program loop.
2. I checked if `argc` is greater than one; if so then it prints the error message `Shell program executes and therefore the shell takes
   no command-line arguments.` Then returns 1 from the main function.
3. By using the `getline()` function I set a default size of 200 characters but let the function reallocate memory as needed.
4. I use Null Terminator '\0' for 'strncat' and newline characters in order to avoid having memory leaks and memory errors occur when running the
   simple shell. 
5. By using `strcmp()` I'm able to detect if the initial command value is `exit` and perform the ending of the program instead of passing it
   to the command executor function. The exit statement does accept a status value to pass on return;
6. Testing with valgrind has shown that there are no leaks in the `./simple_shell` program, I tested multiple proc commands, multiple system
   commands, and exit.

### Part 2

I added a `proc` command to the system using the same mechanism that `exit` was implemented. The `proc` command takes in any valid `/proc`
filesystem file and outputs it's contents to the terminal. All of proc values should be available and I tested all of the required filenames.

## Contributer of this Simple Shell Program
Talha

 
