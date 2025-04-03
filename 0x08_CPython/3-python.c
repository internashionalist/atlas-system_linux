#include <Python.h>
#include <stdio.h>
#include <string.h>

/**
 * print_python_bytes -		prints basic info about Python bytes objects
 * @p:						PyObject pointer (expected to be a bytes object)
 *
 * Description: This function prints the size of the bytes object, its
 *              string representation, and the first 10 bytes (in hex format.)
 *              It prints an error message if the object is not a bytes object.
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i, bytes_to_print;
	char *str;

	setbuf(stdout, NULL);						/* set stdout buffer to NULL */
	printf("[.] bytes object info\n");

	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	/* direct access to structure to avoid forbidden macros */
	size = ((PyVarObject *)p)->ob_size;
	str = ((PyBytesObject *)p)->ob_sval;

	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", str);

	bytes_to_print = (size + 1 < 10 ? size + 1 : 10);	/* first 10 + /0 */
	printf("  first %ld bytes:", bytes_to_print);

	for (i = 0; i < bytes_to_print; i++)
		printf(" %02x", (unsigned char)str[i]);

	printf("\n");
}

/**
 * print_python_float -		prints basic info about Python float objects
 * @p:						PyObject pointer (expected to be a float)
 *
 * Description: This function prints the value of the float object.
 */
void print_python_float(PyObject *p)
{
	double value;				/* value of the float object */

	setbuf(stdout, NULL);		/* set stdout buffer to NULL */
	printf("[.] float object info\n");
	if (!PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	value = ((PyFloatObject *)p)->ob_fval;
	printf("  value: %f\n", value);
}

/**
 * print_python_list -		prints basic info about Python lists
 * @p:						PyObject pointer (expected to be a list)
 *
 * Description: This function prints the size and allocated memory of a Python
 *              list and the type of each element. If an element is a bytes
 *              object, it prints its details by calling print_python_bytes.
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;
	PyListObject *list;

	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	if (!PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	size = ((PyVarObject *)p)->ob_size;
	list = (PyListObject *)p;

	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);

	for (i = 0; i < size; i++)
	{
		/* can't use PyList_Get Item */
		PyObject *item = list->ob_item[i];

		printf("Element %ld: %s\n", i, item->ob_type->tp_name);

		if (PyBytes_Check(item)) /* if item is a bytes object */
			print_python_bytes(item);
		else if (PyFloat_Check(item)) /* if item is a float object */
			print_python_float(item);
	}
}
