#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include "multithreading.h"
#include "list.h"

/**
 * add_factor -	allocate and append a prime factor to the list
 * @list:		list_t where the factor should be stored
 * @factor:		prime factor to add
 *
 * This function allocates memory for a new node in the list and
 * initializes it with the given factor. The node is then added to
 * the end of the list.
 *
 * Return:		0 on success, -1 on allocation failure
 */
static int add_factor(list_t *list, unsigned long factor)
{
	unsigned long *pf = malloc(sizeof(*pf));

	if (!pf)
		return (-1);

	*pf = factor;
	list_add(list, pf);
	return (0);
}

/**
 * factorize_even - extract factor 2 from n until odd
 * @list: list to append factors
 * @n:    pointer to the current integer to divide
 *
 * This function checks if n is even and divides it by 2
 * until it becomes odd. Each time 2 is a factor, it is added
 * to the list. The function continues until n is odd.
 *
 * Return: 0 on success, -1 on allocation failure
 */
static int factorize_even(list_t *list, unsigned long *n)
{
	while (*n % 2 == 0)
	{
		if (add_factor(list, 2) != 0)
			return (-1);
		*n /= 2;
	}
	return (0);
}

/**
 * factorize_odd - extract odd prime factors from n
 * @list: list to append factors
 * @n:    pointer to the current integer to divide
 *
 * This function iterates through odd numbers starting from 3
 * and checks if they are factors of n. If a factor is found,
 * it is added to the list and n is divided by that factor.
 *
 * Return: 0 on success, -1 on allocation failure
 */
static int factorize_odd(list_t *list, unsigned long *n)
{
	unsigned long i;

	for (i = 3; i <= *n / i; i += 2)
	{
		while (*n % i == 0)
		{
			if (add_factor(list, i) != 0)
				return (-1);
			*n /= i;
		}
	}
	return (0);
}

/**
 * prime_factors - factorizes a positive integer into its prime factors
 * @s: string representation of the number to factorize
 *
 * This function takes a string representation of a positive integer,
 * converts it to an unsigned long, and then finds its prime factors.
 *
 * Return: pointer to an allocated list_t with nodes containing pointers to
 *         unsigned long holding each prime factor (in ascending order),
 *         or NULL on failure.
 */
list_t *prime_factors(char const *s)
{
	unsigned long n; /* number to factor */

	char *endptr = NULL; /* end of string pointer */
	list_t *factors; /* list of factors */

	/* check for NULL or empty string */
	if (!s)
		return (NULL);

	/* convert string to unsigned long */
	n = strtoul(s, &endptr, 10);
	if (errno == ERANGE || *endptr != '\0')
		return (NULL); /* invalid number or out of range */

	/* allocate and initialize list */
	factors = malloc(sizeof(*factors));
	if (!factors)
		return (NULL);
	list_init(factors);

	/* extract factors */
	if (factorize_even(factors, &n) != 0 ||
	    factorize_odd(factors, &n) != 0)
		return (factors);

	/* leftover prime factor */
	if (n > 1)
		add_factor(factors, n);

	return (factors);
}
