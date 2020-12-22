NAME	= myftp

CC	= gcc

RM	= rm -f

SRCS	=	./src/main.c \
			./src/server_creation.c \
			./src/server_utils.c \
			./src/clients_management.c \
			./src/client_reader.c \
			./src/linked_list.c \
			./src/str_to_word_array.c \
			./src/string_utils.c \
			./src/file_utils.c \
			./src/commands/fork_utils.c \
			./src/commands/cdup.c \
			./src/commands/cwd.c \
			./src/commands/dele.c \
			./src/commands/help.c \
			./src/commands/list.c \
			./src/commands/noop.c \
			./src/commands/pass.c \
			./src/commands/pasv.c \
			./src/commands/port.c \
			./src/commands/pwd.c \
			./src/commands/quit.c \
			./src/commands/retr.c \
			./src/commands/stor.c \
			./src/commands/user.c


OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -g

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
