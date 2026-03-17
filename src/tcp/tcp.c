#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "usrv/tcp/tcp.h"

// More descriptive aliases
#define SOCK_PROTO_DEFAULT 0
#define SOCK_BIND_STATUS_SUCCESS 0
#define SOCK_LISTEN_STATUS_SUCCESS 0
#define CONNECT_STATUS_SUCCESS 0

int tcp_init()
{
    // initialize connection
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, SOCK_PROTO_DEFAULT);
    if (sockfd == -1) {
        perror("[tcp] socket creation failed. aborting.\n");
        exit(TCP_ERR_SOCK_CREATION_FAILED);
    }
    printf("[tcp] socket successfully created. FD: %d\n", sockfd);

    return sockfd;
}

void tcp_bind(int sockfd, unsigned short port)
{
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    // TODO: what does htonl / htons mean and do in this context?
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    int status_bind = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (status_bind != SOCK_BIND_STATUS_SUCCESS) {
        perror("[tcp] failed to bind socket. aborting.");
        exit(TCP_ERR_SOCK_BIND_FAILED);
    }
    printf("[tcp] socket successfully bound.\n");
}

int tcp_listen(int sockfd, int max_connections)
{
    int status_listen = listen(sockfd, max_connections);
    if (status_listen != SOCK_LISTEN_STATUS_SUCCESS) {
        perror("[tcp] socket listen failed.");
        exit(TCP_ERR_SOCK_LISTEN_FAILED);
    }
    printf("[tcp] server listening.\n");

    int connfd;
    struct sockaddr_in clientsock;
    socklen_t client_len = sizeof(clientsock);

    connfd = accept(sockfd, (struct sockaddr*)&clientsock, &client_len);
    if (connfd == -1) {
        perror("[tcp] server accept failed.");
        exit(TCP_ERR_CONN_ACCEPT_FAILED);
    }
    printf("[tcp] accepted client connection.\n");

    return connfd;
}

void tcp_connect(int sockfd, struct sockaddr_in addr)
{
    // address and port are in little endian -> must reverse to print IPv4
    // convert from LE to BE
    unsigned short port_be = htons(addr.sin_port);
    printf("[tcp] connect: %d.%d.%d.%d:%d\n",
        (addr.sin_addr.s_addr & 0x000000ff) >> 0,
        (addr.sin_addr.s_addr & 0x0000ff00) >> 8,
        (addr.sin_addr.s_addr & 0x00ff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24,
        port_be);
    int status_connect = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (status_connect != CONNECT_STATUS_SUCCESS) {
        perror("[tcp] error while connecting. aborting.");
        exit(TCP_ERR_CONN_CONNECT_FAILED);
    }
    printf("[tcp] successfully established TCP client connection.\n");
}