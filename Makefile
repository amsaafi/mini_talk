CC = cc
CFLAGS = -Wall -Wextra -Wextra

CLIENT_SRC = client.c
BCLIENT_SRC = client_bonus.c
SERVER_SRC = server.c
BSERVER_SRC = server_bonus.c
COMMON_SRC = includes/ft_atoi.c \
             includes/ft_putnbr.c \
             includes/ft_putstr.c

CLIENT_EXE = client
SERVER_EXE = server

BCLIENT_EXE = client_bonus
BSERVER_EXE = server_bonus

all: $(CLIENT_EXE) $(SERVER_EXE)
bonus: $(BCLIENT_EXE) $(BSERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXE) $(CLIENT_SRC) $(COMMON_SRC)

$(SERVER_EXE): $(SERVER_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXE) $(SERVER_SRC) $(COMMON_SRC)

$(BCLIENT_EXE): $(BCLIENT_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(BCLIENT_EXE) $(BCLIENT_SRC) $(COMMON_SRC)

$(BSERVER_EXE): $(BSERVER_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(BSERVER_EXE) $(BSERVER_SRC) $(COMMON_SRC)

clean:
	rm -f $(CLIENT_EXE) $(SERVER_EXE) $(BCLIENT_EXE) $(BSERVER_EXE)