#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

/**
 * current_handler_signal - retrieves current handler of the SIGINT signal
 *
 * Return:					pointer to the current handler of the SIGINT
 *							signal, or NULL on failure
 */
void (*current_handler_signal(void))(int)
{
	void (*sig_handler)(int);

	/* ignore SIGINT temporarily to save current handler */
	sig_handler = signal(SIGINT, SIG_IGN);
	if (sig_handler == SIG_ERR)
	{
		return (NULL);
	}

	signal(SIGINT, sig_handler); /* restore original handler */

	return (sig_handler);
}
