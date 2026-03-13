#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include "tcp/tcp.h"

#define PORT 1234
#define MAX_CONNECTIONS 1
#define BUF_SIZE 8

void server_handle_tcp_comm(int connfd)
{
    char buf[BUF_SIZE];
    while (1) {
        bzero(buf, BUF_SIZE);
        read(connfd, buf, sizeof(buf));
        printf("%s", buf);
    }
}

void start_tcp_server()
{
    int sockfd = init_tcp_conn(PORT, MAX_CONNECTIONS);
    int connfd = wait_accept_tcp_conn(sockfd);
    server_handle_tcp_comm(connfd);
    close(sockfd);
    close(connfd);
}