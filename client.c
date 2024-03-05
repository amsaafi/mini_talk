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


void	send_msg(pid_t sv_pid, char *msg)
{
	unsigned char	c;
	int				nbr_bits;

	while (*msg)
	{
		c = *msg;
		nbr_bits = 8;
		while (nbr_bits--)
		{
			if (c & 0b10000000)
				kill(sv_pid, SIGUSR1);
			else
				kill(sv_pid, SIGUSR2);
			usleep(50);
			c <<= 1;
		}
		msg++;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "Character has been sucessfully receieved!\n", 42);
}

void	config_signals(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_handler = &sig_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		printf("Failed to change SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		printf("Failed to change SIGUSR2's behavior");
}

int	main(int argc, char **argv)
{
	pid_t		sv_pid;

	// args_check(argc, argv);
	sv_pid = atoi(argv[1]);
	config_signals();
	send_msg(sv_pid, argv[2]);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}