#include "sockets.h"
#include "util.c"
/**
 * main - Entry point for the server program.
 *
 * Description: This function starts the server and then blocks indefinitely
 * until the process receives a termination signal.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(void)
{
	int sockfd;						/* server socket file descriptor */

	sockfd = setup_server_socket();	/* call helper function */
	if (sockfd == -1)
		return (EXIT_FAILURE);

	printf("Server listening on port %d\n", PORT);
	fflush(stdout);

	for (;;)						/* infinite loop to accept connections */
		pause();

	/* keep -Werror happy */
	return (EXIT_SUCCESS);
}
