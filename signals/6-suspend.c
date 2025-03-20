#include "signals.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
Write a program that sets a handler for the signal SIGINT, and exits right after the signal is received and handled

Your program does not take any argument
Your program should suspend indefinitely until a signal is received
When a SIGINT is received, you must print Caught %d (where %d must be replaced by the signal number), followed by a new line
After the first SIGINT is received, your program must:
Print Signal received, followed by a new line
Exit with EXIT_SUCCESS
You are not allowed to use the functions exit, sleep or _exit
You are not allowed to use any kind of loop (while, for, do/while)
*/

void sigint_handler(int signum)
{
    printf("Caught %d\n", signum);
    printf("Signal received\n");
    signal(SIGINT, SIG_DFL);
}

int main(void) {
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
        return EXIT_FAILURE;
    }

    pause();

    return EXIT_SUCCESS;
}