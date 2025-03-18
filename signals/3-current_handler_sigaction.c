#include "signals.h"

/*Write a function that retrieves the current handler of the signal SIGINT

Prototype: void (*current_handler_sigaction(void))(int);
Your function returns a pointer to the current handler of SIGINT, or NULL on failure
You have to use the function sigaction (signal is not allowed)
The handler must be unchanged after calling your function
*/

void (*current_handler_sigaction(void))(int)