#include "sockets.h"
#include "util.c"

/**
 * main - Entry point for the client program.
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(int argc, char **argv)
{
	unsigned short port;			/* port number in host byte order */
	int sockfd;						/* socket file descriptor */

	/* check for correct number of arguments */
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	/* parse port number */
	port = parse_port(argv[2]);
	if (port == 0)
		return (EXIT_FAILURE);

	/* connect to the host */
	sockfd = connect_to_host(argv[1], port);
	if (sockfd == -1)
		return (EXIT_FAILURE);

	printf("Connected to %s:%s\n", argv[1], argv[2]);
	close(sockfd);
	return (EXIT_SUCCESS);
}
