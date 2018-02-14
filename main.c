#include <stdio.h> 		// printf
#include <stdlib.h> 	// exit
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // waitpid
#include <unistd.h> 	// fork


// Function each process runs,
// Print -> Sleep -> Print:
void process(int number, int time)
{
	printf("Prosess %d kjører\n", number);
	sleep(time);
	printf("Prosess %d kjørte i %d sekunder\n", number, time);
}

int pid[6];


int main(void)
{
	// First, start fork 0 and 2:

	pid[0] = fork();

	if (pid[0] < 0)
	{
		printf("Failed to create process %d!\n", 0);
	}
	else if( pid[0] == 0)									// Is child.
	{
		process(0, 1);
		exit(0);
	}

	// Parent
	pid[2] = fork();

	if (pid[2] < 0)
	{
		printf("Failed to create process %d!\n", 2);
	}
	else if( pid[2] == 0)									// Is child.
	{
		process(2, 3);
		exit(0);
	}

	// Fork 0 and 2 is started, now wait for 0 to finish to start fork 1 and 4:
	waitpid(pid[0], NULL, 0);

	pid[1] = fork();

	if (pid[1] < 0)
	{
		printf("Failed to create process %d!\n", 1);
	}
	else if( pid[1] == 0)									// Is child.
	{
		process(1, 2);
		exit(0);
	}

	pid[4] = fork();

	if (pid[4] < 0)
	{
		printf("Failed to create process %d!\n", 4);
	}
	else if( pid[4] == 0)									// Is child.
	{
		process(4, 3);
		exit(0);
	}

	// Fork 1 and 4 is started, now wait for 1 and 2 to finish to start fork 3:

	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);

	pid[3] = fork();

	if (pid[3] < 0)
	{
		printf("Failed to create process %d!\n", 3);
	}
	else if( pid[3] == 0)									// Is child.
	{
		process(3, 2);
		exit(0);
	}

	// All other forks are started, now wait for 4 to start the last fork, 5:

	waitpid(pid[4], NULL, 0);

	pid[5] = fork();

	if (pid[5] < 0)
	{
		printf("Failed to create process %d!\n", 5);
	}
	else if( pid[5] == 0)									// Is child.
	{
		process(5, 3);
		exit(0);
	}

	// All forks are started, just wait for the last one to finish:
	waitpid(pid[5], NULL, 0);

	exit(0);
}
