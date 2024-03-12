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

void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static int				bit_index;
	static unsigned char	c = 0;

	(void)context;
	bit_index = 0;
	c = 0;
	if (signum == SIGUSR1)
		c |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		if (c == '\0')
		{
			if (kill(info->si_pid, SIGUSR1) == -1)
				write(1, "Failed to send acknowledgment (SIGUSR1)", 38);
		}
		else
			ft_putstr(c, 1);
		c = 0;
		bit_index = 0;
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
		write(1, "Failed to send acknowledgment (SIGUSR2)", 38);
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("SERVER PID = %d\n\n", pid);
	while (1)
		config_signals();
	return (0);
}
