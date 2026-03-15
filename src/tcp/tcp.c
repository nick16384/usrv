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
// Errors
#define ERR_SOCK_CREATION_FAILED 10000
#define ERR_SOCK_BIND_FAILED     10001
#define ERR_SOCK_LISTEN_FAILED   10002
#define ERR_CONN_ACCEPT_FAILED   10003
#define ERR_CONN_CONNECT_FAILED  10004

int tcp_init(unsigned short port)
{
    // initialize connection
    int sockfd;
    struct sockaddr_in serveraddr;

    sockfd = socket(AF_INET, SOCK_STREAM, SOCK_PROTO_DEFAULT);
    if (sockfd == -1) {
        perror("socket creation failed. aborting.\n");
        exit(ERR_SOCK_CREATION_FAILED);
    }
    printf("socket successfully created. FD: %d\n", sockfd);

    // fill with zeroes?
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    // TODO: what does htonl / htons mean and do in this context?
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    int status_bind = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (status_bind != SOCK_BIND_STATUS_SUCCESS) {
        perror("failed to bind socket. aborting.");
        exit(ERR_SOCK_BIND_FAILED);
    }
    printf("socket successfully bound.\n");

    return sockfd;
}

int tcp_wait_accept_conn(int sockfd, int max_connections)
{
    int status_listen = listen(sockfd, max_connections);
    if (status_listen != SOCK_LISTEN_STATUS_SUCCESS) {
        perror("socket listen failed.");
        exit(ERR_SOCK_LISTEN_FAILED);
    }
    printf("server listening.\n");

    int connfd;
    struct sockaddr_in clientsock;
    socklen_t client_len = sizeof(clientsock);

    connfd = accept(sockfd, (struct sockaddr*)&clientsock, &client_len);
    if (connfd == -1) {
        perror("server accept failed.");
        exit(ERR_CONN_ACCEPT_FAILED);
    }
    printf("accepted client connection.\n");

    return connfd;
}

void tcp_connect(int sockfd, struct sockaddr_in *addr)
{
    printf("connect: %d\n", addr->sin_addr.s_addr >> 24);
    int status_connect = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (status_connect != CONNECT_STATUS_SUCCESS) {
        perror("error while connecting. aborting.");
        exit(ERR_CONN_CONNECT_FAILED);
    }
    printf("successfully established tcp client connection.\n");
}