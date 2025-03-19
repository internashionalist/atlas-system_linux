#include <signal.h>
#include "signals.h"

/**
 * print_hello -		prints "Hello" followed by a newline
 * @signum:				signal number (unused)
 *
 * Description:			this had better be useful.
 *
 * Return:				void
 */
void print_hello(int signum)
{
	(void)signum;
	printf("Hello\n");
}

/**
 * set_print_hello -	blah blah does this file need to exist
 *
 * Description:			because I'm too compulsively thorough to not do it
 *
 * Return:				void
 */
void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}
