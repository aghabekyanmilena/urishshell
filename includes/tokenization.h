/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:16:19 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/19 18:59:12 by atseruny         ###   ########.fr       */
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

extern int	g_err_no;

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
int		limiter_for_dollar(char	c);
char	*return_bacac(char *line, int *i, int k, t_data *db);
void	init_tokens_sharunak(t_data *data_base, t_token *cpy);
void	init_tokens_sharunak_redir(t_token *cpy);
char	*get_operator(char *value, int i, int *j);
int		ka_u_redir_pipe_chi(char c);
void	redirnery(t_token **first, t_token *c, t_token *st, int i);
int		chakert_check_sharunak(char *all, int *i, int *j, t_data *data_base);
char	*get_line(char *line, t_data *db, int *i, int k);

// free
void	free_tokens(t_data *db);
void	free_tok(t_token *c);

//join_3
char	*ft_join_3(char *start, char *mid, char *end);

//shlvl
void	handle_shlvl(t_data *data);
void	update_env(t_data *data, char *key, const char *value);
char	*get_env(char **env, const char *key);



#endif