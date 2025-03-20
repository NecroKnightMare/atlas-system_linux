#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

/*Write a function that retrieves the current handler of the signal SIGINT

Prototype: void (*current_handler_sigaction(void))(int);
Your function returns a pointer to the current handler of SIGINT, or NULL on failure
You have to use the function sigaction (signal is not allowed)
The handler must be unchanged after calling your function
*/

void sigint_handler(int signum)
{
    printf("Hello :) [%d]\n", signum);
    /*use fflush here */
}

void (*current_handler_sigaction(void))(int)
{
    struct sigaction old_sa;

    /*retrieve address SIGINT*/
    if (sigaction(SIGINT, NULL, &old_sa) == -1)
    {
        perror("retrieving error");
        return NULL;
    }

    return old_sa.sa_handler;
}