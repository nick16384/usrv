#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "usrv/tcpserver/tcpserver.h"
#include "usrv/testing/tcpclient.h"

#define VERSION_STRING "2026.03-dev"
#define EXIT_SIGNAL_NONE -1

void exit_clean(int dummy);

int main(int argc, char** argv)
{
    printf("%s%s\n", "Welcome to da micro server (usrv) ver. ", VERSION_STRING);

    printf("cmdline: ");
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    if (argc < 2) {
        perror("Please specify 'server' or 'client'.");
        exit(0);
    }

    signal(SIGINT, exit_clean);
    signal(SIGTERM, exit_clean);
    
    if (strncmp(argv[1], "server", 6) == 0) {
        printf("[main] launching server.\n");
        server_start(1234);
    }
    else if (strncmp(argv[1], "client", 6) == 0) {
        printf("[main] launching client.\n");
        client_start(1235);
        client_connect("127.0.0.1", 1234);
        const char *msg = "Hello, server!";
        client_send(msg, strlen(msg));
    }

    exit_clean(EXIT_SIGNAL_NONE);
    return 0;
}

inline void exit_clean(int signal)
{
    // TODO: do some cleanup when necessary
    if (signal != EXIT_SIGNAL_NONE)
        printf("\n[main] received signal %d\n", signal);
    printf("[main] closing...\n");
    server_exit();
    client_exit();
    exit(0);
}