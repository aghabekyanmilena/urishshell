NAME = minishell

SRC = main.c utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

all: $(NAME)

$(NAME): $(SRC) includes Makefile
	$(CC) $(CFLAGS) -Iincludes $(SRC) $(LIBS) -o $(NAME)

clean:
	@# No object files to remove yet, placeholder for later

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
