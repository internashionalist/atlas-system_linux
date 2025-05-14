#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include "multithreading.h"
#include "list.h"

/**
 * prime_factors -	factorizes a positive integer into its prime factors
 * @s:				string representation of the number to factorize
 *
 * This function takes a string representation of a positive integer,
 * converts it to an unsigned long, and then finds its prime factors.
 *
 * Return:	pointer to an allocated list_t with nodes containing pointers to
 *			unsigned long holding each prime factor (in ascending order),
 * 			or NULL on failure.
 */
list_t *prime_factors(char const *s)
{
	unsigned long n, i; /* current factor */
	char *endptr = NULL; /* end of string pointer */
	list_t *factors; /* list of factors */

	/* check for NULL or empty string */
	if (!s)
		return (NULL);
	
	/* convert string to unsigned long */
	n = strtoul(s, &endptr, 10);
	if (errno == ERANGE || *endptr != '\0' || n == ULONG_MAX)
		return (NULL); /* invalid number or out of range */

	/* allocate and initialize list */
	factors = malloc(sizeof(*factors));
	if (!factors)
		return (NULL);
	list_init(factors);

	/* factor out 2s */
	while (n % 2 == 0)
	{
		unsigned long *pf = malloc(sizeof(*pf));
		if (!pf)
			return (factors); /* list is still valid */
		*pf = 2;
		list_add(factors, pf);
		n /= 2;
	}

	/* factor out odds up to sqrt(n) */
	for (i = 3; i * i <= n; i += 2)
	{
		while (n % i == 0)
		{
			unsigned long *pf = malloc(sizeof(*pf));
			if (!pf)
				return (factors);
			*pf = i;
			list_add(factors, pf);
			n /= i;
		}
	}

	/* if n is prime and greater than 2, add it to the list */
	if (n > 1)
	{
		unsigned long *pf = malloc(sizeof(*pf));
		if (pf)
		{
			*pf = n;
			list_add(factors, pf);
		}
	}

	return (factors);
}
