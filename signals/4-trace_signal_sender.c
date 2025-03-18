#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signals.h"

/**
 * sigquit_printer -	SIGQUIT signal handler & printer
 * @signum:				signal number (SIGQUIT)
 * @info:				pointer to struct with signal details
 * @context:			pointer to struct with signal context (unused)
 *
 * Description:			prints "SIGQUIT sent by <pid>" on receiving SIGQUIT
 *
 * Return:				void
 */
void sigquit_printer(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGQUIT)
	{
		fprintf(stdout, "SIGQUIT sent by %d\n", info->si_pid);
		fflush(stdout);
	}
}

/**
 * trace_signal_sender - sets handler for SIGQUIT using sigaction
 *
 * Description:		initializes struct sigaction variable, sets sa_sigaction
 *					to sigquit_printer, and installs new handler for SIGQUIT.
 *					SA_SIGINFO flag is used so signal info is passed to
 *					handler.
 *
 * Return:			0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	sigaction_t sa;  /* struct to handle signal actions */

	memset(&sa, 0, sizeof(sa));  /* initialize struct to 0 */
	sa.sa_flags = SA_SIGINFO;  /* use sa_sigaction instead of sa_handler */
	sa.sa_sigaction = sigquit_printer;  /* set handler to sigquit_printer */

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		return (-1);
	}

	return (0);
}
