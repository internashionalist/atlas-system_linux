#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

/**
 * caught_printer - handles SIGINT signals, prints a message
 * @signum:			signal number caught
 *
 * Return:			void
 */
void caught_printer(int signum)
{
	printf("Caught %d\n", signum);
}

/**
 * main - sets SIGINT handler and waits for signal
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(void)
{
	sigaction_t sa;						/* sigaction struct */

	sa.sa_handler = caught_printer;		/* set handler */
	sa.sa_flags = 0;					/* set flags */
	sigemptyset(&sa.sa_mask);			/* set mask */
	sigaction(SIGINT, &sa, NULL);		/* update action */
	pause();							/* wait for signal */

	printf("Signal received\n");		/* print message on signal */

	return (EXIT_SUCCESS);
}
