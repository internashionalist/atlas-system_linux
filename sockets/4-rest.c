#include "sockets.h"
#include "util.c"

#define PORT 8080
#define BUFFER_SIZE 4096 /* large enough for a simple HTTP request */

/**
 * trim_cr - remove a trailing CR character (if found).
 * @s: string to trim
 *
 * Description: This function checks for a carriage return at the end of a
 * string and replaces it with a null terminator.
 *
 * Return: void
 */
static void trim_cr(char *s)
{
	size_t len = strlen(s);

	if (len && s[len - 1] == '\r')
		s[len - 1] = '\0';
}

/**
 * handle_client - read, log and answer a single HTTP/1.1 request.
 * @client_fd: connected client socket
 *
 * Description: This function prints the raw request, breaks down the
 * request‑line into Method / Path / Version and sends a response.
 *
 * Return: void
 */
static void handle_client(int client_fd)
{
	char buffer[BUFFER_SIZE + 1]; /* +1 for nul-byte */
	const char reply[] = "HTTP/1.1 200 OK\r\n\r\n";
	ssize_t n_read;				/* number of bytes read from client */
	char method[16] = {0};		/* method buffer */
	char path[1024] = {0};		/* path buffer */
	char version[16] = {0};		/* version buffer */

	memset(buffer, 0, sizeof(buffer)); /* init buffer to zero */

	n_read = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (n_read <= 0)
		return;

	printf("Raw request: \"%.*s\"\n", (int)n_read, buffer);

	sscanf(buffer, "%15s %1023s %15s", method, path, version);

	/* strip CR in case path/version have one */
	trim_cr(path);
	trim_cr(version);

	printf("Method: %s\n", method);
	printf("Path: %s\n", path);
	printf("Version: %s\n", version);

	/* send success response */
	send(client_fd, reply, sizeof(reply) - 1, 0);
}

/**
 * main - tiny blocking HTTP server.
 *
 * Description: This function sets up a server socket, listens, accepts
 * connections, and handles each client. It reads a single HTTP/1.1 request,
 * logs it, and sends a response.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(void)
{
	int server_fd = setup_server_socket(); /* helper from util.c */

	if (server_fd == -1)
		return (EXIT_FAILURE);

	printf("Server listening on port 8080\n");

	for (;;)
	{
		struct sockaddr_in client_addr;
		socklen_t addr_len = sizeof(client_addr);
		int client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
							   &addr_len);
		if (client_fd == -1)
		{
			perror("accept");
			continue; /* try next connection if accept fails */
		}

		printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

		handle_client(client_fd);

		close(client_fd); /* done with this client */
	}

	/* not reachable */
	close(server_fd);
	return (EXIT_SUCCESS);
}
