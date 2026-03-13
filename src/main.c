#include <stdio.h>

int exit_clean();

int main(int argc, char** argv)
{
    printf("Welcome to da micro server (usrv).\n");

    printf("cmdline: ");
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    return exit_clean();
}

inline int exit_clean()
{
    // TODO: do some cleanup when necessary
    printf("\n");
    return 0;
}