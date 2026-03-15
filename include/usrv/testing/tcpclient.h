#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

/// @brief Start a TCP client, creating a TCP socket.
/// @param port The port to establish uplink from.
void client_start(int port);

/// @brief Connect to a TCP server.
/// @param address_str The server address as a string (e.g. "127.0.0.1").
/// @param port The server port.
void client_connect(char *address_str, in_port_t port);

/// @brief Send n bytes of msg to the server with address + port.
/// @param msg The message.
/// @param n Number of bytes of the message to send.
void client_send(char *msg, int n);

/// @brief Close the TCP client and all associated TCP connections.
void client_exit(void);

#endif