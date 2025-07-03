/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:16:19 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 19:53:48 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "../libft/libft.h"

typedef struct s_token	t_token;
typedef struct s_data	t_data;
typedef struct s_command	t_cmd;

/* what enum do is to give names to numbers, it is a special data type 
that contains a set of named ineteger constants */

typedef enum e_token_type
{
	WORD,			// 0
	S_PIPE,			// 1 single pipe |
	D_PIPE,			// 2 double pipe ||
	REDIR_IN,		// 3 <
	REDIR_OUT,		// 4 >
	APPEND,			// 4 >>
	HEREDOC,		// 5 <<
	S_AND,			// 6 single and &
	D_AND,			// 7 double and &&
	INFILE,			// 8 after <
	LIMITER,		// 9 after <<
	OUTFILE,		// 10 after >
	OUTFILE_APPEND,	// 11 after >>
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

#include "pipex.h"

// init utils
void	add_token(t_token **head, char *value, t_token_type type);
char	*read_quoted_string(char *line, int *i, char **env);
char	*read_word(char *line, int *i);
void	init_tokens(char *line, t_data *data_base);


// this is shlvl
// void handle_shlvl(t_data *data);


#endif