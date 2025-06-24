#include "sockets.h"
#include "util.c"

/**
 * main - Entry point for the server program.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(void)
{
	int server_fd, client_fd; /* server and client socket file descriptors */
	struct sockaddr_in client_addr; /* client address struct */
	socklen_t addr_len = sizeof(client_addr); /* size of struct */
	char ip_str[INET_ADDRSTRLEN]; /* buffer for client IP address */

	/* set up the server socket */
	server_fd = setup_server_socket();
	if (server_fd == -1)
		return (EXIT_FAILURE);

	printf("Server listening on port %d\n", PORT);
	fflush(stdout);

	/* accept a client connection */
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd == -1)
	{
		perror("accept");
		close(server_fd);
		return (EXIT_FAILURE);
	}

	/* print the client's IP address */
	if (inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str)))
		printf("Client connected: %s\n", ip_str);
	else
		perror("inet_ntop");

	close(client_fd);
	close(server_fd);

	return (EXIT_SUCCESS);
}
