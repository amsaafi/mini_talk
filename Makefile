# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samsaafi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 14:10:27 by samsaafi          #+#    #+#              #
#    Updated: 2024/03/15 14:10:31 by samsaafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Compiler = cc
CFLAGS = -Wall -Wextra -Werror
NAME = client
SERVER = server

INC = includes/ft_atoi.c \
		includes/ft_putnbr.c \
		includes/ft_putstr.c \

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

all: $(NAME) $(SERVER)

$(NAME): client.c $(INC)
	$(Compiler) $(CFLAGS) $^ -o $@

$(SERVER): server.c $(INC)
	$(Compiler) $(CFLAGS) $^ -o $@

clean:
	@rm -f server
	@rm -f client
	@rm -f client_bonus
	@rm -f server_bonus

fclean: clean

re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): server_bonus.c $(INC)
	$(Compiler) $(CFLAGS) $^ -o $(SERVER_BONUS)

$(CLIENT_BONUS): client_bonus.c $(INC)
	$(Compiler) $(CFLAGS) $^ -o $(CLIENT_BONUS)