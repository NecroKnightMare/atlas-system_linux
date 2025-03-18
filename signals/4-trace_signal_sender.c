#include "signals.h"

/*Write a function that defines a handler for the signal SIGQUIT (Control-\ in a shell)

Prototype: int trace_signal_sender(void);
The handler must print SIGQUIT sent by <pid> each time a SIGQUIT (and only a SIGQUIT) is caught
Where <pid> must be replaced by the PID of the process that sent the signal
Your function must return 0 on success, or -1 on error
*/

int trace_signal_sender(void)