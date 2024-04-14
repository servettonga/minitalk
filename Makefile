SERVER	=   server
CLIENT	=   client
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I lib -L . -lftprintf
LIB		=	libftprintf.a
SRCS 	=	src/server.c \
			src/client.c
OBJS	=	server \
			client

all: $(LIB) $(OBJS)

$(LIB):
	make -C lib
	cp lib/$(LIB) .

server: src/server.c $(LIB)
	$(CC) $(CFLAGS) -o $(SERVER) src/server.c

client: src/client.c src/utils.c $(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT) src/client.c

clean:
	rm -f $(LIB)
	make clean -C lib

fclean: clean
	rm -f $(OBJS)

re: fclean all
