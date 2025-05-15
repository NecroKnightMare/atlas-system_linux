#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
// Works -- needed to add to commits

// Global thread safe printing
// Will help print one at a time instead of simultaneously
static pthread_mutex_t print_mutex;

/**
 * __attribute__((constructor)) init_mutex - Initializes the mutex before any thread runs
 */
__attribute__((constructor))
void init_mutex(void)
{
    pthread_mutex_init(&print_mutex, NULL);
}

/**
 * __attribute__((destructor)) destroy_mutex - Cleans up the mutex after execution
 */
__attribute__((destructor))
void destroy_mutex(void)
{
    pthread_mutex_destroy(&print_mutex);
}

/**
 * tprintf - Thread-safe printf with mutex protection
 * @format: Formatted string to print
 * Return: Number of characters printed
 */
int tprintf(char const *format, ...)
{
    va_list args;
    int ret;

    pthread_mutex_lock(&print_mutex);  // Locks
    printf("[%lu] ", pthread_self());

    va_start(args, format);
    ret = vprintf(format, args);
    va_end(args);

    pthread_mutex_unlock(&print_mutex);  // Unlocks

    return ret;
}
