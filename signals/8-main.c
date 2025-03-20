#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * main - Simple program, printing its PID and running infinitely
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

void handle_sigquit(int sig) {
    printf("Caught %d\n", sig);
    exit(EXIT_SUCCESS);
}

int main(void)
{
    pid_t pid;

    pid = getpid();
    if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
    {
        perror("signal");
        return 1;
    }
    printf("PID: %d\n", (int)pid);
    while (98)
    {
        printf("Waiting ...\n");
        sleep(1);
    }
    return (EXIT_SUCCESS);
}