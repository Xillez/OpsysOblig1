#include <stdio.h> 		// printf
#include <stdlib.h> 	// exit
#include <unistd.h> 	// fork
#include <sys/wait.h> 	// waitpid
#include <sys/types.h> 	// pid_t


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
    pid[0] = fork();
    if (pid[0] < 0) printf("Failed to create process %d!\n", 0);
    else if( pid[0] == 0)
    {
        process(0, 1);										// Child
        exit(0);
    }

    // Parent
    pid[2] = fork();
    if (pid[2] < 0) printf("Failed to create process %d!\n", 2);
    else if( pid[2] == 0)
    {
        process(2, 3);										// Child
        exit(0);
    }

    waitpid(pid[0], NULL, 0);

    pid[1] = fork();
    if (pid[1] < 0) printf("Failed to create process %d!\n", 1);
    else if( pid[1] == 0)
    {
        process(1, 2);										// Child
        exit(0);
    }

    pid[4] = fork();
    if (pid[4] < 0) printf("Failed to create process %d!\n", 4);
    else if( pid[4] == 0)
    {
        process(4, 3);										// Child
        exit(0);
    }

    waitpid(pid[1], NULL, 0);
    waitpid(pid[2], NULL, 0);

    pid[3] = fork();
    if (pid[3] < 0) printf("Failed to create process %d!\n", 3);
    else if( pid[3] == 0)
    {
        process(3, 2);										// Child
        exit(0);
    }

    waitpid(pid[4], NULL, 0);

    pid[5] = fork();
    if (pid[5] < 0) printf("Failed to create process %d!\n", 5);
    else if( pid[5] == 0)
    {
        process(5, 3);										// Child
        exit(0);
    }

    waitpid(pid[5], NULL, 0);

    exit(0);
}
