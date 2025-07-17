/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:52:05 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/17 19:55:36 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenization.h"

void	init_tokens_sharunak(t_data *data_base, t_token *cpy)
{
	data_base->pipes_count = 0;
	while (cpy)
	{
		if (ft_strcmp(cpy->value, "|") == 0)
		{
			(data_base->pipes_count)++;
			cpy->type = S_PIPE;
		}
		init_tokens_sharunak_redir(cpy);
		cpy = cpy->next;
	}
}

char	*get_operator(char *value, int i, int *j)
{
	(*j)++;
	if (value[i] == '<')
	{
		if (value[i + 1] == '<')
		{
			(*j)++;
			return (ft_strdup("<<"));
		}
		return (ft_strdup("<"));
	}
	else if (value[i] == '>')
	{
		if (value[i + 1] == '>')
		{
			(*j)++;
			return (ft_strdup(">>"));
		}
		return (ft_strdup(">"));
	}
	else if (value[i] == '|')
		return (ft_strdup("|"));
	else
		(*j)--;
	return (NULL);
}

int	ka_u_redir_pipe_chi(char c)
{
	if (c && c != '<' && c != '>' && c != '|')
		return (1);
	return (0);
}

void	init_tokens_sharunak_redir(t_token *cpy)
{
	if (ft_strcmp(cpy->value, "<") == 0)
	{
		cpy->type = REDIR_OUT;
		if (cpy->next)
			cpy->next->type = INFILE;
	}
	else if (ft_strcmp(cpy->value, "<<") == 0)
	{
		cpy->type = HEREDOC;
		if (cpy->next)
			cpy->next->type = LIMITER;
	}
	else if (ft_strcmp(cpy->value, ">") == 0)
	{
		cpy->type = REDIR_OUT;
		if (cpy->next)
			cpy->next->type = OUTFILE;
	}
	else if (ft_strcmp(cpy->value, ">>") == 0)
	{
		cpy->type = APPEND;
		if (cpy->next)
			cpy->next->type = OUTFILE_APPEND;
	}
}

void	redirnery(t_token **first, t_token *c, t_token *st, int i)
{
	t_token	*tmp;
	int		j;

	while (c)
	{
		i = 0;
		j = 0;
		while (ka_u_redir_pipe_chi(c->value[i]))
			i++;
		if (c->value[i])
		{
			if (i > 0)
				add_token(&st, ft_substr(c->value, 0, i), WORD);
			add_token(&st, get_operator(c->value, i, &j), WORD);
			if (c->value[i + j])
				add_token(&st, ft_substr(c->value, i + j,
						ft_strlen(c->value) - i - j), WORD);
		}
		else
			add_token(&st, ft_strdup(c->value), WORD);
		tmp = c->next;
		free_tok(c);
		c = tmp;
	}
	*first = st;
}
