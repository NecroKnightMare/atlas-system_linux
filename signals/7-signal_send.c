#include "signals.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*Write a program that sends the signal SIGINT to a process, given its PID

Usage: signal_send <pid>
Where <pid> is the PID of the process to send a signal to
If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with EXIT_FAILURE
<pid> won’t be 0
Your program must return EXIT_SUCCESS on success, or EXIT_FAILURE
You’re not allowed to have more than 1 function in your file
*/

// void sigint_handler(int signum)
// {
//     printf("Waiting ... %d\n", signum);
//     printf("PID: %d\n", (int)getpid());
// }

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pid = atoi(argv[1]);

    if (kill(pid, SIGINT) == -1)
    {
        perror("kill failed");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}