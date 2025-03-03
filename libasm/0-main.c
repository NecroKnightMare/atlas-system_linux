#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "\0"

extern size_t asm_strlen(const char *str);

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void) {
    // __asm(
    assert(strlen(S1) == asm_strlen(S1));
    assert(strlen(S2) == asm_strlen(S2));
    assert(strlen(S3) == asm_strlen(S3));

    printf("All good!\n");
    return (EXIT_SUCCESS);
    // );
}