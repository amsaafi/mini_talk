#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sigtype)
{
    write(1, "HANDLER EXEC\n", 13);
}

int main(int ac, int *av[])
{
    struct sigaction sg_action;

    sg_action.sa_handler = handler;
    sigemptyset(&sg_action.sa_mask);
    sg_action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sg_action, NULL);
    while(1)
    {
        sleep(1);
    }
}