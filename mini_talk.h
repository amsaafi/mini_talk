/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:35 by samsaafi          #+#    #+#             */
/*   Updated: 2024/03/12 14:28:36 by samsaafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putstr(char c, int fd);
int		ft_atoi(const char *nptr);
void	ft_putnbr(int nb);

#endif