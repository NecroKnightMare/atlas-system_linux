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
extern int asm_strncmp(const char *s1, const char *s2, size_t n);

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strncmp(S1, S3, 1) == asm_strncmp(S1, S3, 1));
    assert(strncmp(S1, S3, 11) == asm_strncmp(S1, S3, 11));
    assert(strncmp(S1, S3, 15) == asm_strncmp(S1, S3, 15));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}