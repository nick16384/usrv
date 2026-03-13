#ifndef TCP_H
#define TCP_H

/// @brief Initialize a TCP connection.
/// @return The socket file descriptor (FD)
int init_tcp_conn(int port, int max_connections);

/// @brief Waits until an incoming TCP connection is available and accepts it.
/// @param sockfd A previously established socket file descriptor
/// @return The connection file descriptor (FD).
int wait_accept_tcp_conn(int sockfd);

#endif