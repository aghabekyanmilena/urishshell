/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:16:19 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/15 15:31:46 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include "pipex.h"
# include "../libft/libft.h"

typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_command	t_cmd;
typedef struct s_pipex		t_pipex;
typedef struct s_limiter	t_limiter;

extern int g_err_no;

/* what enum do is to give names to numbers, it is a special data type 
that contains a set of named ineteger constants */

typedef enum e_token_type
{
	WORD,			// 0
	S_PIPE,			// 1 single pipe |
	REDIR_IN,		// 2 <
	REDIR_OUT,		// 3 >
	APPEND,			// 4 >>
	HEREDOC,		// 5 <<
	INFILE,			// 6 after <
	LIMITER,		// 7 after <<
	OUTFILE,		// 9 after >
	OUTFILE_APPEND,	// 10 after >>
}	t_token_type;

struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
};

struct s_command
{
	char				*value;
	t_token_type		type;
	struct s_command	*next;
};

struct s_data
{
	t_token	*token;
	t_pipex	*pipex;
	char	**env;
	int		pipes_count;
	int		command_count;
};

// init utils
void	add_token(t_token **head, char *value, t_token_type type);
void	init_tokens(char *line, t_data *data_base);

// free
void	free_tokens(t_data *db);

//shlvl
void	handle_shlvl(t_data *data);
void	update_env(t_data *data, const char *key, const char *value);
char	*get_env(char **env, const char *key);

#endif