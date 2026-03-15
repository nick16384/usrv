#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "usrv/tcp/tcp.h"
#include "usrv/tcpserver/tcpserver.h"

#define MAX_CONNECTIONS 1
#define BUF_SIZE 32

#define CONN_READ_EOF 0
#define CONN_READ_ERROR -1

#define ERR_CONN_READ_ERROR 20000

static int sockfd = -1, connfd = -1;

static void handle_comm(void)
{
    char buf[BUF_SIZE];
    while (1) {
        bzero(buf, BUF_SIZE);
        int status = read(connfd, buf, sizeof(buf));
        switch (status) {
            case CONN_READ_ERROR:
                perror("[server] error reading from connection.");
                exit(ERR_CONN_READ_ERROR);
            case CONN_READ_EOF:
                printf("[server] receive terminated with EOF.");
                return;
        }
        printf("%s", buf);
    }
}

void server_start(unsigned short port)
{
    sockfd = tcp_init(port);
    connfd = tcp_wait_accept_conn(sockfd, MAX_CONNECTIONS);
    handle_comm();
}

void server_exit(void)
{
    printf("[server] closing server and TCP connection.\n");
    sockfd:
    if (sockfd == -1) { goto connfd; }
    close(sockfd);
    sockfd = -1;

    connfd:
    if (connfd == -1) { return; }
    close(connfd);
    connfd = -1;
    return;
}