#include "multithreading.h"

/**
 * tprintf - uses the printf family to print out a given formatted string
 * @format: format string
 *
 * This function is a wrapper around the printf function
 * that prints the formatted string to stdout.
 *
 * Return: the number of characters printed
 */
int tprintf(const char *format, ...)
{
	va_list args;
	int ret;

	printf("[%ld] ", pthread_self());

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);
	return (ret);
}
