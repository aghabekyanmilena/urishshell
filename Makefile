NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror $(INC_DIRS) -g3 -fsanitize=address
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
LIBFT = libft/libft.a
HEADERS = includes/tokenization.h includes/syntax.h includes/built_in.h includes/pipex.h

LIBS_DIR = libraries
READLINE = readline
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

SRC_DIR = src
SYNTAX = $(SRC_DIR)/syntax
TOKEN = $(SRC_DIR)/token
PIPEX= $(SRC_DIR)/pipex
BUILTIN = $(SRC_DIR)/built-in
SIGNALS = $(SRC_DIR)/signals

SRC = \
	$(SRC_DIR)/main.c $(SRC_DIR)/shlvl.c \
	$(TOKEN)/token.c $(TOKEN)/token_utils.c $(TOKEN)/token_redir.c $(TOKEN)/token_sharunak.c \
	$(SYNTAX)/syntax_check.c \
	$(BUILTIN)/built_utils.c $(BUILTIN)/echo.c $(BUILTIN)/exit.c $(BUILTIN)/env.c $(BUILTIN)/cd.c $(BUILTIN)/pwd.c $(BUILTIN)/export.c $(BUILTIN)/unset.c $(BUILTIN)/export_util.c\
	$(PIPEX)/pipex_start.c $(PIPEX)/utils.c $(PIPEX)/pipeing.c $(PIPEX)/heredoc.c $(PIPEX)/get_next_line.c $(PIPEX)/get_next_line_utils.c\
	$(PIPEX)/files.c $(PIPEX)/no_pipe.c \
	$(SIGNALS)/init_signals.c 


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
