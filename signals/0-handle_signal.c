/*Needs to interrupt signal after the third time. Works as intended otherwise.
*/

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>


/*Write a function that set a handler for the signal SIGINT

Prototype: int handle_signal(void);
Your function must return 0 on success, or -1 on error
The program should print Gotcha! [<signum>] followed by a new line, every time Control-C is pressed (See example below)
where <signum> must be replaced with the signal number that was caught
sigaction(2) is not allowed
*/

/*made function for print call*/
void sigint_handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
    /*Use fflush here*/
}

int handle_signal(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        return -1;
    }
    return 0;
}