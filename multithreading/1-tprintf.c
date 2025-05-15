#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdarg.h>
#include "multithreading.h"

/**
 * tprintf - Prints a formatted string, prepended with the calling thread ID
 * @format: The format string
 * Return: 0 on success, negative value on error
 */
int tprintf(char const *format, ...)
{
	va_list args;
	int ret;

	/* Print thread ID before formatted output*/*
	printf("[%lu] ", pthread_self());

	/* Process variable arguments*/
	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	return (ret);
}
