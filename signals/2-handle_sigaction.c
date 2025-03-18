#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
 * handle_sigaction -	sets handler for SIGINT signal using sigaction
 *
 * Return:              0 on success, -1 on failure
 */
int handle_sigaction(void)
{
    struct sigaction sa;  /* struct to handle signal actions */

    memset(&sa, 0, sizeof(sa));  /* initialize struct to 0 */
    sa.sa_handler = gotcha_printer;  /* set handler to gotcha_printer */

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        return (-1);
    }

    return (0);
}
