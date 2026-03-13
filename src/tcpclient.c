#include <unistd.h>
#include <strings.h>
#include "tcp/tcp.h"

#define PORT 1234
#define ADDR inet_addr("127.0.0.1")
#define MAX_CONNECTIONS 1
#define BUF_SIZE 8

// FIXME: Compile test client as separate binary and add testing util functions

/// @brief Expects a connection file descriptor and handles communication with the client. The method blocks indefinitely.
/// @param connfd A previously established connection file descriptor
void client_handle_tcp_comm(int connfd)
{
    char buf[BUF_SIZE];
    char* str = "Hello, server!";
    write(connfd, str, sizeof(str));
    return;
}

void start_tcp_client()
{
    return;
    int sockfd = init_tcp_conn(PORT, MAX_CONNECTIONS);
    int connfd = wait_accept_tcp_conn(sockfd);
    client_handle_tcp_comm(connfd);
    close(sockfd);
    close(connfd);
}