#include "signal.h"
#include <stdio.h>
#include <signal.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

void print_hello(int sig);

/*test print function to compile task 3*/
void set_print_hello(void);
// {
//     struct sigaction sa;

//     sa.sa_handler = print_hello;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;

//     if (sigaction(SIGINT, &sa, NULL) == -1) {
//         perror("sigaction failed"); 
//     }
// }