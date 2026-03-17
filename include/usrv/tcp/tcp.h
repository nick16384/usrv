#ifndef TCP_H
#define TCP_H

#include <sys/socket.h>

// Errors
#define TCP_ERR_SOCK_CREATION_FAILED 10000
#define TCP_ERR_SOCK_BIND_FAILED     10001
#define TCP_ERR_SOCK_LISTEN_FAILED   10002
#define TCP_ERR_CONN_ACCEPT_FAILED   10003
#define TCP_ERR_CONN_CONNECT_FAILED  10004

/// @brief Initialize a TCP socket.
/// @return The socket file descriptor (FD)
int tcp_init();

/// @brief Binds an address and port to a socket (colloq. "naming the socket").
/// @param sockfd The socket fd
/// @param port The socket port
void tcp_bind(int sockfd, unsigned short port);

/// @brief Waits until an incoming TCP connection is available and accepts it.
/// @param sockfd A previously established socket file descriptor
/// @param max_connections The maximum amount of connections to listen for.
/// @return The connection file descriptor (FD).
int tcp_listen(int sockfd, int max_connections);

/// @brief Connect (as a client) to a server.
/// @param sockfd The socket file descriptor of the client.
/// @param addr The address + port struct.
/// @note It seems like the struct needs to be passed by value instead of reference. Will investigate why in the future.
void tcp_connect(int sockfd, struct sockaddr_in addr);

#endif