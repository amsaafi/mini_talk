/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:37 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/12 14:27:39 by samsaafi         ###   ########.fr       */
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

int	main(int ac, char *av[])
{
	int	pid;

	pid = ft_atoi(av[1]);
	send_msg(pid, av[2]);
	return (0);
}
