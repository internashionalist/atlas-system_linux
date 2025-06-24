#include "sockets.h"

/**
 * setup_server_socket - Create, bind and listen on a TCP socket.
 *
 * Description: This helper encapsulates all steps needed to open a listening
 * IPv4/TCP socket bound to PORT on every interface.
 *
 * Return: File descriptor of the listening socket on success, -1 on failure.
 */
int setup_server_socket(void)
{
	int sockfd;				 /* server socket file descriptor */
	struct sockaddr_in addr; /* server address struct */
	int opt = 1;			 /* option for setsockopt */

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

	memset(&addr, 0, sizeof(addr));			  	/* clear address struct */
	addr.sin_family = AF_INET;				  	/* set addr family to IPv4 */
	addr.sin_addr.s_addr = htonl(INADDR_ANY); 	/* bind to any address */
	addr.sin_port = htons(PORT);			  	/* set port number */

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

	return (sockfd);				/* return the socket file descriptor */
}

/**
 * parse_port - Convert string to an unsigned‑short TCP port.
 * @str: port string from argv
 *
 * Return: port in host byte order, or 0 on error (and prints message).
 */
unsigned short parse_port(const char *str)
{
    char *endptr;
	/* convert string to unsigned long */
    unsigned long port_ul = strtoul(str, &endptr, 10); 

    if (*endptr != '\0' || port_ul > 65535) /* check for valid conversion */
    {
        fprintf(stderr, "Invalid port: %s\n", str);
        return (0);
    }
    return ((unsigned short)port_ul);
}

/**
 * connect_to_host - resolve @host, open socket and connect on @port.
 * @host: hostname or dotted‑quad IPv4 address.
 * @port: TCP port in host byte order.
 *
 * Return: connected socket fd on success, -1 on error (prints message).
 */
int connect_to_host(const char *host, unsigned short port)
{
    int sockfd;							/* socket file descriptor */
    struct sockaddr_in server_addr;		/* server address struct */

	/* init server address struct */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(port);

	/* convert host to network byte order */
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) != 1)
    {
        struct hostent *he = gethostbyname(host); /* resolve hostname */

        if (!he || he->h_addrtype != AF_INET)
        {
            fprintf(stderr, "Could not resolve host: %s\n", host);
            return (-1);
        }
		/* copy resolved address to server_addr */
        memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);
    }
	/* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return (-1);
    }
	/* connect to the server */
    if (connect(sockfd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(sockfd);
        return (-1);
    }
    return (sockfd);
}
