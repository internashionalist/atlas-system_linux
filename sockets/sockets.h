#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345		/* default listening port */
#define BACKLOG 10		/* number of pending connections allowed */

/**
 * struct sockaddr_in - IPv4 socket address structure
 * @sin_family:			address family (must be AF_INET)
 * @sin_port:			port number in network byte order
 * @sin_addr:			IPv4 address
 * @sin_zero:			padding (unused)
 *
 * Description: For Betty
 *
 * This structure is used to specify an endpoint address for IPv4 sockets.
 */

#endif /* SOCKETS_H */
