#include <stdio.h>
#include <pthread.h>
#include "multithreading.h"

void *thread_entry(void *arg)
{
    char *str = (char *)arg;
    printf("%s\n", str);
    return NULL;
}