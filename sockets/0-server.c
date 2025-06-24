#include "sockets.h"

/**
 * setup_server_socket - Create, bind and listen on a TCP socket.
 *
 * Description: This helper encapsulates all steps needed to open a listening
 * IPv4/TCP socket bound to PORT on every interface.
 *
 * Return: File descriptor of the listening socket on success, -1 on failure.
 */
/**
 * struct sockaddr_in - IPv4 socket address structure
 * @sin_family:			address family (must be AF_INET)
 * @sin_port:			port number in network byte order
 * @sin_addr:			IPv4 address
 * @sin_zero:			padding (unused)
 *
 * Description: For Betty
 */

static int setup_server_socket(void)
{
	int sockfd;					/* server socket file descriptor */
	struct sockaddr_in addr;	/* server address struct */
	int opt = 1;				/* option for setsockopt */

	/* IPv4/TCP socket creation */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return (-1);
	}

	/* allow address reuse */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt");
		close(sockfd);
		return (-1);
	}

	memset(&addr, 0, sizeof(addr));				/* clear address struct */
	addr.sin_family = AF_INET;					/* set addr family to IPv4 */
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	/* bind to any address */
	addr.sin_port = htons(PORT);				/* set port number */

	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("bind");
		close(sockfd);
		return (-1);
	}

	if (listen(sockfd, BACKLOG) == -1)			/* set socket to listen */
	{
		perror("listen");
		close(sockfd);
		return (-1);
	}

	return (sockfd);
}

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
