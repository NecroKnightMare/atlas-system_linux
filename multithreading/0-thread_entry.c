#include <stdio.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * thread_entry - Entry point for a new thread
 * @arg: Pointer to thread argument (expected as a string)
 *
 * Description:
 * This function prints the given string argument and then
 * properly terminates the thread using `pthread_exit()`.
 *
 * Return: Always returns NULL
 */

void *thread_entry(void *arg)
{
	char *str = (char *)arg;

	printf("%s\n", str);
	/* terminates the thread*/
	pthread_exit(NULL);
	return (NULL);
}
