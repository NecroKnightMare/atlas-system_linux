#include "signals.h"
/*Write a function that set a handler for the signal SIGINT

Prototype: int handle_sigaction(void);
Your function must return 0 on success, or -1 on error
The program should print Gotcha! [<signum>] followed by a new line, every time Control-C is pressed (See example below)
where <signum> must be replaced with the signal number that was caught
signal(2) is not allowed
*/

int handle_sigaction(void)