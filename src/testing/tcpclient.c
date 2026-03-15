#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "usrv/tcp/tcp.h"
#include "usrv/testing/tcpclient.h"

#define MAX_CONNECTIONS 1

int sockfd = -1;

void client_start(int port)
{
    sockfd = tcp_init(port);
}

void client_connect(char *address_str, in_port_t port)
{
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(address_str);
    serveraddr.sin_port = port;
    tcp_connect(sockfd, &serveraddr);
}

void client_send(char *msg, int n)
{
    printf("sending client message: %s\n", msg);
    write(sockfd, msg, n);
}

void client_exit(void)
{
    // TODO: tell the server to shutdown the connection?
    if (sockfd == -1) { return; }
    close(sockfd);
    sockfd = -1;
}