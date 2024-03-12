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

void	send_msg(int pid, char *str)
{
	unsigned char	c;
	int				bit;

	while (*str)
	{
		c = *str;
		bit = 8;
		while (bit > 0)
		{
			if ((c >> bit - 1) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(255);
			bit--;
		}
		str++;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "Character has been sucessfully receieved!\n", 42);
}

int	main(int ac, char *av[])
{
	int					pid;
	struct sigaction	sa;

	// check_args(ac, av);
	pid = atoi(av[1]);
	sa.sa_handler = &sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_msg(pid, av[2]);
	return (0);
}
