#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

/*Write a function that defines a handler for the signal SIGQUIT (Control-\ in a shell)

Prototype: int trace_signal_sender(void);
The handler must print SIGQUIT sent by <pid> each time a SIGQUIT (and only a SIGQUIT) is caught
Where <pid> must be replaced by the PID of the process that sent the signal
Your function must return 0 on success, or -1 on error
*/

void sigint_handler(int signum)
{
    printf("SIGQUIT sent by [%d]\n", signum);
    /*use fflush here */
}

int trace_signal_sender(void) {
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Not found");
        return -1;
    }
    return 0;
}