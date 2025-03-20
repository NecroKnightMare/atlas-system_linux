#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Write a program that prints a description of a given signal

Usage: ./describe <signum>
Where <signum> is the signal number to be described
If the number of arguments is not correct, your program must print Usage: %s <signum> (where %s is argv[0]), followed by a new line, and exit with EXIT_FAILURE
You’re not allowed to have more than 1 function in your file
You’re not allowed to have more than 12 lines in your function
You can assume that if a parameter is given, it will be a number
*/
int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <signum>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*convert string to integer*/
    int signum = atoi(argv[1]);
    char *signal_name = strsignal(signum);

    if (signal_name)
    {
    printf("%d: %s\n", signum, signal_name);
    return (EXIT_SUCCESS);
    } else {
        printf("%d: Unknown signal\n", signum);
        return (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
