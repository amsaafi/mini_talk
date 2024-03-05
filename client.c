/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:37 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/04 13:06:07 by samsaafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

static int glb = 0;

void    sig_handler(int sigint, siginfo_t *info, void *context)
{
    static  int i;
    
    i = 0;
    glb = 1;
    if (sigint == SIGUSR2)
        i++;
    else if (sigint == SIGUSR1)
        write(1, "recieved bits\n", 14);
}

int char_to_bin(char c, int pid)
{
    int x;
    int bit;

    bit = 8;
    while (bit > 0)
    {
        x = 0;
        
        if ((c >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while (glb == 0)
        {
            if (x == 42)
            {
                write(1, "TIMEOUT: no response from server\n", 33);
                exit(1);
            }
            x++;
            usleep(84);
        }
        glb = 0;
        bit--;
    }
    return (0);
}

int main(int ac, char *av[])
{
    struct sigaction   sa;
    char    *msg;
    int pid;
    int byte;

    if (ac != 3)
    {
        ft_putstr("Usage: ./Client \"PID\" \"message\" \n");
        return (1);
    }
    pid = ft_atoi(av[1]);
    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sig_handler;

    msg = av[2];
    byte = 0;
    while (msg[byte] != '\0')
    {
        char_to_bin(msg[byte], pid);
        byte++;
    }
    char_to_bin('\0', pid);
    return (0);
}
