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
    sockfd = tcp_init();
}

void client_connect(char *address_str, unsigned int port)
{
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(address_str);
    serveraddr.sin_port = htons((in_port_t)port);
    tcp_connect(sockfd, serveraddr);
}

void client_send(char *msg, int n)
{
    printf("sending client message: %s\n", msg);
    write(sockfd, msg, n);
}

void client_exit(void)
{
    printf("[client] closing server connection & TCP socket.\n");
    // TODO: tell the server to shutdown the TCP connection explicitly?
    if (sockfd == -1) { return; }
    close(sockfd);
    sockfd = -1;
}