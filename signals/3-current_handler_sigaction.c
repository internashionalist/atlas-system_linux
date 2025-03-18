#include <signal.h>
#include <stdio.h>
#include "signals.h"

/**
 * current_handler_sigaction - retrieves current handler of the SIGINT signal
 *
 * Description: uses sigaction with a NULL pointer for a NEW action to get the
 *				CURRENT action for SIGINT
 *
 * Return:		pointer to current handler of the SIGINT signal (sa_handler),
 *				or NULL on failure
 */
void (*current_handler_sigaction(void))(int)
{
	sigaction_t sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
	{
		return (NULL);
	}

	return (sa.sa_handler);
}
