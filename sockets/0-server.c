#include "sockets.h"

/**
 * setup_server_socket -	helper to create and configure a server socket
 *
 * Description: This function creates a TCP socket, binds it to the specified
 * port, allows address reuse, and sets it to listen for incoming connections.
 *
 * Return:					file descriptor on success, -1 on failure
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
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt");
        close(sockfd);
        return (-1);
    }

    /* bind to 0.0.0.0:PORT */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind");
        close(sockfd);
        return (-1);
    }

    /* start listening */
    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        close(sockfd);
        return (-1);
    }

    return (sockfd);
}

/**
 * main - entry point for the server program
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
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
