#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#define ERR_CONN_READ_ERROR 20000

/// @brief Start a TCP server.
/// @param port The port to listen on.
void server_start(unsigned short port);

/// @brief Close the TCP server and all associated connections.
void server_exit(void);

#endif