/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:37 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/16 13:51:13 by samsaafi         ###   ########.fr       */
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
	__pid_t	pid;

	if (ac == 3)
	{
		check_arg(av[1]);
		pid = ft_atoi(av[1]);
		if (pid == 0 || pid == -1)
			exit(1);
		send_msg(pid, av[2]);
	}
	return (0);
}
