#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define C1  'n'
#define C2  'S'
#define C3  's'

extern size_t asm_strlen(const char *str);
extern int asm_strcmp(const char *s1, const char *s2);
extern int asm_strncmp(const char *s1, const char *s2, size_t n);
extern char *asm_strchr(const char *s, int c);

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strchr(S1, C1) == asm_strchr(S1, C1));
    assert(strchr(S1, C2) == asm_strchr(S1, C2));
    assert(strchr(S1, C3) == asm_strchr(S1, C3));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}