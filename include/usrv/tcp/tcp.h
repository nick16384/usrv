#ifndef TCP_H
#define TCP_H

/// @brief Initialize a TCP connection.
/// @return The socket file descriptor (FD)
int tcp_init(unsigned short port);

/// @brief Waits until an incoming TCP connection is available and accepts it.
/// @param sockfd A previously established socket file descriptor
/// @param max_connections The maximum amount of connections to listen for.
/// @return The connection file descriptor (FD).
int tcp_wait_accept_conn(int sockfd, int max_connections);

/// @brief Connect (as a client) to a server.
/// @param sockfd The socket file descriptor of the client.
/// @param addr The address + port struct.
void tcp_connect(int sockfd, struct sockaddr_in *addr);

#endif