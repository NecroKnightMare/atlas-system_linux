#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"

extern size_t asm_strlen(const char *str);
extern int asm_strcmp(const char *s1, const char *s2);

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strcmp(S1, S1) == asm_strcmp(S1, S1));
    assert((strcmp(S1, S2)) == (asm_strcmp(S1, S2) > 0));
    assert((strcmp(S1, S3)) == (asm_strcmp(S1, S3) < 0));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}