# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salah <salah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 14:05:24 by salah             #+#    #+#              #
#    Updated: 2024/03/15 14:05:25 by salah            ###   ########.fr        #
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