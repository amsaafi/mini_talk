/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:06:16 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/18 16:26:28 by samsaafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	handle_sigusr(int signum)
{
	static int				bit_index;
	static unsigned char	c;

	if (signum == SIGUSR1)
		c |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		ft_putstr(c, 1);
		c = 0;
		bit_index = 0;
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigusr;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	__pid_t	pid;

	pid = getpid();
	ft_putnbr(pid);
	while (1)
		config_signals();
	return (0);
}
