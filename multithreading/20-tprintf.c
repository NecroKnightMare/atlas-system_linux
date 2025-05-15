#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include "multithreading.h"
/* Works -- needed to add to commits */

/* Global thread safe printing*/
/* Will help print one at a time instead of simultaneously */
static pthread_mutex_t print_mutex;

/**
 * init_mutex - Initializes a global mutex for thread synchronization
 *
 * Description:
 * This function sets up a mutex to ensure safe access to shared resources
 * in a multithreaded environment.
 */
__attribute__((constructor))
void init_mutex(void)
{
	pthread_mutex_init(&print_mutex, NULL);
}

/**
 * destroy_mutex - Cleans up and destroys the global mutex
 *
 * Description:
 * Ensures proper resource cleanup by destroying the mutex after use.
 */
__attribute__((destructor))
void destroy_mutex(void)
{
	pthread_mutex_destroy(&print_mutex);
}

/**
 * tprintf - Thread-safe printf with timestamp
 * @format: Format string for output
 *
 * Description:
 * Prints formatted output with a timestamp in a multithreaded environment.
 * Ensures output consistency by synchronizing threads.
 *
 * Return: Number of characters printed
 */
int tprintf(char const *format, ...)
{
	va_list args;
	int ret;

	pthread_mutex_lock(&print_mutex);  /*Locks*/
	printf("[%lu] ", pthread_self());

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	pthread_mutex_unlock(&print_mutex);  /*Unlocks*/

	return (ret);
}
