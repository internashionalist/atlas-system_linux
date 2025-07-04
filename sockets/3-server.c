#include "sockets.h"
#include "util.c"

#define PORT 12345 /* default listening port */

/**
 * main - Entry point for the server program.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(void)
{
	int server_fd, client_fd;		/* server & client socket file descriptors */
	sockaddr_in_t client_addr;		/* client address struct */
	socklen_t addr_len = sizeof(client_addr); /* size of client addr struct */
	char ip_str[INET_ADDRSTRLEN];	/* buffer for client IP address */
	char buf[1024];					/* buffer for received message */
	ssize_t n;						/* number of bytes received */

	server_fd = setup_server_socket(); /* create, bind & listen on TCP socket */
	if (server_fd == -1)
		return (EXIT_FAILURE);

	printf("Server listening on port %d\n", PORT);
	fflush(stdout);
	/* wait for a client connection */
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd == -1)
	{
		perror("accept");
		close(server_fd);
		return (EXIT_FAILURE);
	}
	/* client connected, print its IP address */
	if (inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str)))
		printf("Client connected: %s\n", ip_str);
	else
		perror("inet_ntop");
	/* receive a message from the client */
	n = recv(client_fd, buf, sizeof(buf) - 1, 0);
	if (n > 0)
	{
		buf[n] = '\0';
		printf("Message received: \"%s\"\n", buf);
	}
	else if (n == -1)
		perror("recv");

	close(client_fd);
	close(server_fd);
	return (EXIT_SUCCESS);
}
