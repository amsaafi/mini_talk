/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:37 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/15 14:39:49 by samsaafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_msg(__pid_t pid, char *str)
{
	unsigned char	c;
	int				bit;

	while (*str)
	{
		c = *str;
		bit = 8;
		while (bit > 0)
		{
			if ((c >> (bit - 1)) & 1)
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

void	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			str++;
		else
			exit(1);
	}
}

int	main(int ac, char *av[])
{
	__pid_t				pid;
	struct sigaction	sa;

	if (ac == 3)
	{
		check_arg(av[1]);
		pid = ft_atoi(av[1]);
		sa.sa_handler = &sig_handler;
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		send_msg(pid, av[2]);
	}
	return (0);
}
