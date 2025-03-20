/*Needs to interrupt signal after the third time. Works as intended otherwise.
*/

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

/*Write a function that set a handler for the signal SIGINT

Prototype: int handle_sigaction(void);
Your function must return 0 on success, or -1 on error
The program should print Gotcha! [<signum>] followed by a new line, every time Control-C is pressed (See example below)
where <signum> must be replaced with the signal number that was caught
signal(2) is not allowed
*/



/*Same as file 0, changed syntax*/
void sigint_handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
    /*use fflush here */
}

int handle_sigaction(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("Not found");
        return -1;
    }
    return 0;
}