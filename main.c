#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void error(const char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s target1 target2 ...\n", argv[0]);
        exit(1);
    }

    signal(SIGCHLD, SIG_IGN);

    for (int i = 1; i < argc; ++i)
    {
        pid_t pid = fork();
        if (pid < 0)
            error("Error on fork()");

        if (pid == 0)
        {
            execlp("ping", "ping", "-c", "4", argv[i], NULL);
            perror("Error on execl()");
        }
    }
    return 0;
}

