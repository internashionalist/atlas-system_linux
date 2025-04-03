#include <Python.h>
#include <stdio.h>
#include <limits.h>
#include <longintrepr.h>

/**
 * print_python_int -			prints a Python integer.
 * @p:							PyObject pointer (expected to be an int)
 *
 * Description: This function converts a Python int to a C unsigned long
 *              int (or prints errors on failure) and prints the value.
 */
void print_python_int(PyObject *p)
{
	PyLongObject *obj;					/* pointer to struct*/
	Py_ssize_t ndigits, i;				/* number of digits in int, index */
	int negative;						/* negative flag */
	unsigned long base, result = 0, power = 1;

	setbuf(stdout, NULL);				/* unbuffer to avoid output issues */
	if (!PyLong_Check(p))				/* validity check */
	{
		printf("Invalid Int Object\n");
		return;
	}

	obj = (PyLongObject *)p;
	negative = (((PyVarObject *)obj)->ob_size < 0);

	/* Python3.9 conversion took FOREVER to figure out */
	ndigits = (((PyVarObject *)obj)->ob_size < 0) ?
			  -((PyVarObject *)obj)->ob_size : ((PyVarObject *)obj)->ob_size;
	base = 1UL << PyLong_SHIFT;

	for (i = 0; i < ndigits; i++)
	{
		unsigned long d = obj->ob_digit[i];			/* digit value */

		if (d != 0 && power > ULONG_MAX / d)		/* overflow check */
		{
			printf("C unsigned long int overflow\n");
			return;
		}
		unsigned long add = d * power;				/* convert digit */

		if (result > ULONG_MAX - add)
		{
			printf("C unsigned long int overflow\n");
			return;
		}
		result += add;								/* add to result */

		if (i != ndigits - 1)						/* if not last digit */
		{
			if (power > ULONG_MAX / base)
			{
				printf("C unsigned long int overflow\n");
				return;
			}
			power *= base;
		}
	}

	if (negative)									/* if negative */
		printf("-%lu\n", result);
	else
		printf("%lu\n", result);
}
