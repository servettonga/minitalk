SERVER	=   server
CLIENT	=   client
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I lib -L./lib -lftprintf
LIB		=	lib/libftprintf.a
SRCS 	=	src/server.c \
			src/client.c
OBJS	=	server \
			client

all: $(LIB) $(OBJS)

$(LIB):
	make -C lib

server: $(SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $(SERVER) src/server.c

client: $(SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT) src/client.c

clean:
	rm -f $(LIB)
	make clean -C lib

fclean: clean
	rm -f $(OBJS)
	make fclean -C lib

re: fclean all
