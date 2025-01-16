#ifndef LAPS_H_
#define LAPS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
    int id;
    int laps;
    struct Car *next;
} Car;

void race_state(int *id, size_t size);

#endif
