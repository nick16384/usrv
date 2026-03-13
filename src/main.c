#include <stdio.h>
#include "tcpserver.h"
#include "tcpclient.h"

#define VERSION_STRING "2026.03-dev"

int exit_clean();

int main(int argc, char** argv)
{
    printf("%s%s\n", "Welcome to da micro server (usrv) ver. ", VERSION_STRING);

    printf("cmdline: ");
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    // TODO: header files? tcp? icmp ping? then http.
    start_tcp_server();
    start_tcp_client();

    return exit_clean();
}

inline int exit_clean()
{
    // TODO: do some cleanup when necessary
    printf("\n");
    return 0;
}