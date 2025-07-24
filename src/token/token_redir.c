/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:22:02 by anush             #+#    #+#             */
/*   Updated: 2025/07/24 17:42:54 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

int	ka_u_redir_pipe_chi(char c)
{
	if (c != '<' && c != '>' && c != '|')
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

int	get_token_from_redir(t_token **head, char *value, int *i, int *j)
{
	int		k;

	k = 0;
	if (!value[(*i) + (*j)] || !ka_u_redir_pipe_chi(value[(*i) + (*j)]))
	{
		if (*j > 0)
			add_token(head, ft_substr(value, *i, *j), WORD);
		if (!ka_u_redir_pipe_chi(value[(*i) + (*j)]))
		{
			add_token(head, get_operator(value, (*i) + (*j), &k), WORD);
			(*i) += k;
		}
		return (1);
	}
	return (0);
}

void	redir_sharunak(char *value, int *i, int *j)
{
	while (value[(*i) + (*j)] && ka_u_redir_pipe_chi(value[(*i) + (*j)]))
	{
		if (value[(*i) + (*j)] == '"')
		{
			(*j)++;
			while (value[(*i) + (*j)] && value[(*i) + (*j)] != '"')
				(*j)++;
		}
		else if (value[(*i) + (*j)] == '\'')
		{
			(*j)++;
			while (value[(*i) + (*j)] && value[(*i) + (*j)] != '\'')
				(*j)++;
		}
		(*j)++;
	}
}

void	redirnery(t_token **first, t_token *c, t_token *head, int i)
{
	t_token	*tmp;
	int		j;

	while (c)
	{
		i = 0;
		while (c->value[i])
		{
			j = 0;
			while (ft_isspace(c->value[i]))
				i++;
			while (c->value[i + j])
			{
				redir_sharunak(c->value, &i, &j);
				if (get_token_from_redir(&head, c->value, &i, &j))
					break ;
			}
			i += j;
		}
		tmp = c->next;
		free_tok(c);
		c = tmp;
	}
	*first = head;
}
