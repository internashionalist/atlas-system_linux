#include "multithreading.h"

/*
 * thread_entry -	entry point for new thread
 * @arg:			holds address of a string that must be printed,
 *					followed by \n
 *
 * Return:			void
 */
void *thread_entry(void *arg)
{
	char *str = (char *)arg;

	printf("%s\n", str);
	pthread_exit(NULL);
}
