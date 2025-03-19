#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

/**
 * main - sends SIGINT to a process using kill function
 * @argc: argument count (as integer)
 * @argv: argument vector (as string)
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[])
{
	if (argc != 2)  /* arg count check */
	{
		fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pid = (pid_t)atoi(argv[1]);  /* convert arg string to pid (int) */

	if (kill(pid, SIGINT) == -1)  /* send SIGINT to process */
	{
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
