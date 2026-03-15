#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "tcpserver.h"
#include "tcpclient.h"

#define VERSION_STRING "2026.03-dev"

void exit_clean(int dummy);

int main(int argc, char** argv)
{
    printf("%s%s\n", "Welcome to da micro server (usrv) ver. ", VERSION_STRING);

    printf("cmdline: ");
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    signal(SIGINT, exit_clean);
    signal(SIGTERM, exit_clean);

    // TODO: header files? tcp? icmp ping? then http.
    server_start();
    start_tcp_client();

    exit_clean(0);
    return 0;
}

inline void exit_clean(int dummy)
{
    // TODO: do some cleanup when necessary
    printf("\nclosing...\n");
    exit(0);
}