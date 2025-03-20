/*Works as intended*/

#include "signals.h"
#include <signal.h>
#include <stdio.h>

/*Write a function that retrieves the current handler of the signal SIGINT

Prototype: void (*current_handler_signal(void))(int);
Your function returns a pointer to the current handler of SIGINT, or NULL on failure
You are not allowed to use sigaction(2)
The handler must be unchanged after calling your function
*/


void (*current_handler_signal(void))(int) {
    void (*handler)(int);

    /*temporarily set to SIGINT*/
    handler = signal(SIGINT, SIG_IGN);
    if (handler == SIG_ERR) 
    {
        perror("Error setting");
        return NULL;
    }

    /*restore to original handler*/
    if (signal(SIGINT, handler) == SIG_ERR)
    {
        perror("Error restoring");
        return NULL;
    }

    return handler;
}