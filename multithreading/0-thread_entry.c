#include "multithreading.h"

/*
 * thread_entry -	entry point for new thread
 * @arg:			holds address of a string that must be printed,
 *					followed by \n
 *
 * Description:		Function that prints the string passed as argument
 *					by the thread that created it. The function then
 *					terminates the thread with pthread_exit.
 *
 * Return:			void
 */
void *thread_entry(void *arg)
{
	char *str = (char *)arg;

	printf("%s\n", str);
	pthread_exit(NULL):
}
