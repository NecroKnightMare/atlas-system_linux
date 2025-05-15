#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "multithreading.h"

/**
 * prime_factors - Factorizes number into a list of prime factors
 * @s: String representation of the number to factorize
 *
 * Return: List of prime factors, or NULL on failure
 */
list_t *prime_factors(char const *s)
{
	list_t *factors;
	unsigned long n;

	if (!s || !strlen(s)) /* Ensure valid input */
	{
		return (NULL);
	}
	factors = list_init(NULL);
	if (!factors)
	{       
		return (NULL);
	}
	n = strtoul(s, NULL, 10);
	if (n < 2) /* No need to factorize 0 or 1 */
	{
		free(factors);
		return (NULL);
	}

	if (n == 2) /* Handle edge case for 2 */
	{
		unsigned long *factor = malloc(sizeof(unsigned long));
		if (!factor)
		{
			list_destroy(factors, free);
			free(factors);
			return (NULL);
		}
		*factor = 2;
		list_add(factors, factor);
		return (factors);
	}

	/* Handle factorization by 2 separately */
	while (n % 2 == 0)
	{
		unsigned long *factor = malloc(sizeof(unsigned long));
		if (!factor)
		{
			list_destroy(factors, free);
			free(factors);
			return (NULL);
		}
		*factor = 2;
		list_add(factors, factor);
		n /= 2;
	}

	/* Check odd factors up to sqrt(n) */
	for (unsigned long i = 3; i * i <= n; i += 2)
	{
		while (n % i == 0)
		{
			unsigned long *factor = malloc(sizeof(unsigned long));
			if (!factor)
			{
				list_destroy(factors, free);
				free(factors);
				return (NULL);
			}
			*factor = i;
			list_add(factors, factor);
			n /= i;
		}
	}

	/* If remaining n is prime, add it */
	if (n > 1)
	{
		unsigned long *factor = malloc(sizeof(unsigned long));
		if (!factor)
		{
			list_destroy(factors, free);
			free(factors);
			return (NULL);
		}
		*factor = n;
		list_add(factors, factor);
	}

	return (factors);
}
