/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:06:16 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/04 13:06:17 by samsaafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void    bin_to_char(int signum, char *c)
{
    static int bit_index = 7;

    if (signum == SIGUSR1)
        *c |= (1 << bit_index);
    else if (signum == SIGUSR2)
        *c &= ~(1 << bit_index);

    bit_index--;

    if (bit_index < 0)
        bit_index = 7;
}

void    sig_handler(int signum, siginfo_t *info, void *context)
{
    static int pid;
    static int i;
    static char c;

    (void)context;
    pid = 0;
    c = '\0';
    i = 0;
    if (pid == 0)
        pid = info->si_pid;
    bin_to_char(signum, &c);
    if (++i == 8)
    {
        i = 0;
        if (c == '\0')
        {
            kill(pid, SIGUSR1);
            pid = 0;
            return;
        }
        printf("%c", c);
        c = '\0';
    }
    kill(pid, SIGUSR2);
}

int main(int ac, int *av[])
{
    struct sigaction sa;

    printf("Server PID: %d\n", getpid());
    sa.sa_sigaction = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    
    while (1)
    {
        pause();
    }
    return (0);
}
