#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"

extern int asm_strcmp(const char *s1, const char *s2)

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strncmp(S1, S3) == asm_strncmp(S1, S3));
    assert(strncmp(S1, S3) == asm_strncmp(S1, S3));
    assert(strncmp(S1, S3) == asm_strncmp(S1, S3));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}