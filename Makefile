CC = cc

NAME = minishell
READLINE = readline
LIBS_DIR = libraries
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

CFLAGS = -g -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address

READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = ./includes/tokenization.h

OBJS_DIR = objects/

SRCS_NAME =	init.c init_utils.c

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH) -lncurses > /dev/null

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR) > /dev/null
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(LIBS_DIR)/$(READLINE):
	@echo "Loading required libraries..."
	@./$(LIBS_DIR)/config_readline readline > /dev/null

clean:
	@$(RM) $(OBJS)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(LIBS_DIR)/$(READLINE)
	@rm -rf $(OBJS_DIR)
	@rm -rf $(LIBFTDIR)
	@make -s clean -C $(LIBS_DIR)/readline-8.2

config:
	mkdir -p readline_local
	./readline_config.sh readline_local

re: fclean all

.PHONY: all clean fclean re