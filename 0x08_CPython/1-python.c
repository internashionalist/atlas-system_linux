#include <Python.h>
#include <stdio.h>

/**
 * print_python_list -	prints basic info about Python lists
 * @p:					PyObject pointer (expected to be a list)
 *
 * Description:         This function prints size, allocated size,
 *                      and type for each element of a Python list.
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;				/* size of list, index */
	PyListObject *list;				/* PyListObject struct */

	printf("[*] Python list info\n");
	if (!PyList_Check(p))           /* check if p is list */
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	size = PyList_Size(p);          /* get size of list */
	list = (PyListObject *)p;       /* cast PyObject to PyListObject */

	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);

	for (i = 0; i < size; i++)      /* iterate through list */
	{
		PyObject *item = PyList_GetItem(p, i);  /* get item at i */

		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
	}
}
