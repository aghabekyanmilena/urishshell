/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:16:19 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/05 16:35:21 by miaghabe         ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_command	t_cmd;

/* what enum do is to give names to numbers, it is a special data type 
that contains a set of named ineteger constants */

// int	g_exit_status = 0; // global variable for exit codes

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
	char	**env;
	int		pipes_count;
};

# include "pipex.h"

// init utils
void	add_token(t_token **head, char *value, t_token_type type);
void	init_tokens(char *line, t_data *data_base);

// free
void	free_tokens(t_data *db);
void	dollar_bacel(t_data *db);
char	*get_env(char **env, const char *key);

#endif