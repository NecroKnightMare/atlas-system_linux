#include "signal.h"
#include <stdio.h>
#include <signal.h>

void print_hello(int sig);

/*test print function to compile task 1*/
void set_print_hello(void);
// {
//     signal(SIGINT, print_hello);
// }