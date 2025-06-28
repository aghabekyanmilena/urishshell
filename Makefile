NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror $(INC_DIRS)
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
LIBFT = libft/libft.a
HEADERS = includes/tokenization.h includes/syntax.h includes/built_in.h

LIBS_DIR = libraries
READLINE = readline
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

SRC_DIR = src
SYNTAX = $(SRC_DIR)/syntax
TOKEN = $(SRC_DIR)/token
BUILTIN = $(SRC_DIR)/built-in

SRC = \
	$(SRC_DIR)/main.c \
	$(TOKEN)/token.c \
	$(TOKEN)/token_utils.c \
	$(SYNTAX)/syntax_check.c \
	$(SYNTAX)/operator_check.c \
	$(BUILTIN)/built_utils.c \
	$(BUILTIN)/echo.c \
	$(BUILTIN)/exit_1.c \
	$(BUILTIN)/env.c

OBJS_DIR = objects
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH) $(LIBFT) -lncurses

$(OBJS_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft/

$(LIBS_DIR)/$(READLINE):
	@echo "Loading required libraries..."
	@./$(LIBS_DIR)/config_readline readline > /dev/null

clean:
	@$(RM) $(OBJS)
	@make -C libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(LIBS_DIR)/$(READLINE)
	@rm -rf $(OBJS_DIR)
	@make -C libft/ fclean
	@make -s -C $(LIBS_DIR)/readline-8.2 clean

config:
	mkdir -p readline_local
	./readline_config.sh readline_local

re: fclean all

.PHONY: all clean fclean re config
