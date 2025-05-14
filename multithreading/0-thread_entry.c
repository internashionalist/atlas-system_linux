#include "multithreading.h"

/**
 * thread_entry - entry point for a new thread
 * @arg: address of string to print, followed by '\n'
 *
 * Prints the string passed as argument by the thread that created it,
 * then terminates the thread.
 *
 * Return: NULL
 */
void *thread_entry(void *arg)
{
	char *str = (char *)arg;

	printf("%s\n", str);
	pthread_exit(NULL);
}
