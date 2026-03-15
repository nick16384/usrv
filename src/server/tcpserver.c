#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include "tcp/tcp.h"

#define PORT 1234
#define MAX_CONNECTIONS 1
#define BUF_SIZE 32

#define CONN_READ_EOF 0
#define CONN_READ_ERROR -1

#define ERR_CONN_READ_ERROR 20000

int sockfd, connfd;

void handle_comm()
{
    char buf[BUF_SIZE];
    while (1) {
        bzero(buf, BUF_SIZE);
        int status = read(connfd, buf, sizeof(buf));
        switch (status) {
            case CONN_READ_ERROR:
                perror("error reading from connection.");
                exit(ERR_CONN_READ_ERROR);
            case CONN_READ_EOF:
                printf("receive terminated with EOF.");
                return;
        }
        printf("%s", buf);
    }
}

void server_start(unsigned short port)
{
    sockfd = init_tcp_conn(port, MAX_CONNECTIONS);
    connfd = wait_accept_tcp_conn(sockfd);
    handle_comm(connfd);
}

void server_exit()
{
    close(sockfd);
    close(connfd);
}