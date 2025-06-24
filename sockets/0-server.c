#include "sockets.h"

/**
 * main -	entry point for the server program
 *
 * Description: This program creates a TCP server that listens on port 12345,
 *			accepts incoming connections, and allows address reuse. It runs
 *			indefinitely until terminated by a signal.
 *
 * Return:	EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(void)
{
	int sockfd = -1;				/* socket file descriptor */
	struct sockaddr_in addr;		/* socket address structure */

	/* IPv4/TCP socket creation, error check */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return (EXIT_FAILURE);
	}

	/* allow address reuse, error check */
	int opt = 1;
	if (setsockopt(
		sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt");
		close(sockfd);
		return (EXIT_FAILURE);
	}

	/* bind to 0.0.0.0:12345 */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	/* bind socket, error check */
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("bind");
		close(sockfd);
		return (EXIT_FAILURE);
	}

	/* start listening for connections, error check */
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		close(sockfd);
		return (EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);
	fflush(stdout);

	/* main loop - until killed */
	for (;;)
		pause();

	/* keep -Werror happy */
	return (EXIT_SUCCESS);
}
