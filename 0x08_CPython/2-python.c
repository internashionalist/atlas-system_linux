#include <Python.h>
#include <stdio.h>
#include <string.h>


/**
 * print_python_bytes - prints basic info about Python bytes objects
 * @p: PyObject pointer (expected to be a bytes object)
 *
 * Description: This function prints the size of the bytes object, the
 *              string representation, and first 10 bytes (in hex format.)
 *
 * Return: None
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i, bytes_to_print;		/* size, index, bytes to print */
	char *str;								/* string representation */

	printf("[.] bytes object info\n");		/* header */
	if (!PyBytes_Check(p))					/* check if p is bytes */
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	/* can't use PyBytes_Size or PyBytes_AsString */
	size = ((PyVarObject *)p)->ob_size;
	str = ((PyBytesObject *)p)->ob_sval;

	printf("  size: %ld\n", size);			/* print size */
	printf("  trying string: %s\n", str);	/* try to print string */

	/* print first 10 bytes or less - including /0 (this took forever) */
	bytes_to_print = (size + 1 < 10 ? size + 1 : 10);

	printf("  first %ld bytes:", bytes_to_print);	/* print first bytes */

	for (i = 0; i < bytes_to_print; i++)		/* iterate through bytes */
		printf(" %02x", (unsigned char)str[i]);	/* print each in hex format */

	printf("\n");
}


/**
 * print_python_list -		prints basic info about Python lists.
 * @p:						PyObject pointer (expected to be a list)
 *
 * Description: This function prints the size and allocated space of a Python
 *              list plus the type of each element. If an element is a
 *              bytes object, it also prints details by calling function
 *              print_python_bytes.
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;					/* size of list, index */
	PyListObject *list;					/* PyListObject struct */

	printf("[*] Python list info\n");	/* header for list info */
	if (!PyList_Check(p))				/* check if p is list */
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	/* can't use PyList_Size or PyList_GetItem */
	size = ((PyVarObject *)p)->ob_size;
	list = (PyListObject *)p;

	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);
	for (i = 0; i < size; i++)
	{
		PyObject *item = list->ob_item[i];		/* get item at i */

		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (strcmp(item->ob_type->tp_name, "bytes") == 0)	/* if bytes */
			print_python_bytes(item);	/* call print_python_bytes */
	}
}
