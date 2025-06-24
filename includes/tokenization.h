/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:16:19 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/24 16:15:28 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_token	t_token;
typedef struct s_data	t_data;

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
};

// init utils
void	add_token(t_token **head, char *value, t_token_type type);
char	*read_quoted_string(char *line, int *i, char **env);
char	*read_word(char *line, int *i);


#endif