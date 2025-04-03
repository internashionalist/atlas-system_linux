#include <Python.h>
#include <stdio.h>

/**
 * print_python_string -	prints basic info about Python string objects
 * @p:						PyObject pointer (expected to be a string)
 *
 * Description: This function prints the type, length, and value of a Python
 *              string. It prints an error message if the object is not a
 *				string.
 */
void print_python_string(PyObject *p)
{
	const char *str;					/* UTF-8 string */
	Py_ssize_t len;						/* length of string */

	setbuf(stdout, NULL);				/* unbuffered (for correct order)*/
	printf("[.] string object info\n");
	if (!PyUnicode_Check(p))			/* string check */
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}

	if (PyUnicode_READY(p) == -1)			/* ready check */
	{
		printf("  [ERROR] Failed to READY string object\n");
		return;
	}

	if (PyUnicode_IS_COMPACT_ASCII(p))	/* compact ascii or unicode obj */
		printf("  type: compact ascii\n");
	else
		printf("  type: compact unicode object\n");

	len = PyUnicode_GetLength(p);		/* hopefully this macro is okay */
	printf("  length: %zd\n", len);

	/* get UTF-8 string */
	str = PyUnicode_AsUTF8(p);			/* conversion to UTF-8 */
	if (str == NULL)					/* conversion check */
	{
		printf("  [ERROR] Failed to CONVERT to UTF-8\n");
		return;
	}
	printf("  value: %s\n", str);
}
