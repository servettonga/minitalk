NAME	=   server
CLIENT	=   client
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I lib
LIB		=	lib/libftprintf.a
LIBFLG	=	-L lib -lftprintf
SRC_DIR	=	src
SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)

all: $(NAME) $(CLIENT)

$(LIB):
	@make -C lib

$(NAME): $(SERVER_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(NAME) $(LIBFLG)

$(CLIENT): $(CLIENT_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT) $(LIBFLG)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make fclean -C lib
	@rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	@rm -f $(NAME) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
