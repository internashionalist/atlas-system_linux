#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

/**
 * main - puts out a description for a given signal
 * @argc: argument count (as integer)
 * @argv: argument vector (as string)
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[])
{
	if (argc != 2)  /* argument count check */
	{
		fprintf(stderr, "Usage: %s <signum>\n", argv[0]);  /* print usage */
		return (EXIT_FAILURE);
	}

	int signum = atoi(argv[1]);  /* convert arg string to int */

	printf("%d: %s\n", signum, strsignal(signum));  /* print signal description */

	return (EXIT_SUCCESS);
}
