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

void handle_sigusr(int signum, siginfo_t *info, void *context)
{
    static int bit_index = 0;
    static unsigned char c = 0;

    (void)context;

    if (signum == SIGUSR1)
        c |= (1 << (7 - bit_index));

    bit_index++;

    if (bit_index == 8)
    {
        if (c == '\0')
        {
            // End of message, send acknowledgement
            if (kill(info->si_pid, SIGUSR1) == -1)
                printf("Failed to send acknowledgement (SIGUSR1)");
        }
        else
        {
            // Process the received character
            ft_putstr(c, STDOUT_FILENO);
        }

        c = 0;
        bit_index = 0;
    }

    // Send acknowledgment signal
    if (kill(info->si_pid, SIGUSR2) == -1)
        printf("Failed to send acknowledgment (SIGUSR2)");
}


// 1 -> 00000001
// a -> 01100001

void	config_signals(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &handle_sigusr;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		printf("Failed to change SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		printf("Failed to change SIGUSR2's behavior");
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("SERVER PID = %d\n\n", pid);
	while (1)
		config_signals();
	return (EXIT_SUCCESS);
}
