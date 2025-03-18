#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

/**
 * gotcha_printer -		prints "Gotcha!" on receiving a signal
 *						(plus signal number)
 * @signum:				signal number to print
 *
 * Return:				void
 */
void gotcha_printer(int signum)
{
	fprintf(stdout, "Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal -		handles SIGINT signal when received
 *
 * Return:				0 on success, -1 on failure
 */
int handle_signal(void)
{
	if (signal(SIGINT, gotcha_printer) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}
