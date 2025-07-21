/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:22:02 by anush             #+#    #+#             */
/*   Updated: 2025/07/22 00:22:11 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

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

void	redirnery(t_token **first, t_token *c, t_token *head, int i)
{
	t_token	*tmp;
	int		j;
	int		k;

	while (c)
	{
		i=0;
		while (c->value[i])
		{
			j = 0;
			while (ft_isspace(c->value[i]))
				i++;
			while (c->value[i + j])
			{
				while (c->value[i+j] && ka_u_redir_pipe_chi(c->value[i + j]) )//&& !ft_isspace(c->value[i + j]))
				{
					if (c->value[i+j] == '"')
					{
						j++;
						while (c->value[i+j] && c->value[i+j] != '"')
							j++;
					}
					else if (c->value[i+j] == '\'')
					{
						j++;
						while (c->value[i+j] && c->value[i+j] != '\'')
							j++;
					}
					j++;
				}
				k = 0;
				if (!c->value[i+j] || !ka_u_redir_pipe_chi(c->value[i + j]) )//|| ft_isspace(c->value[i + j]))
				{
					if (j>0)
						add_token(&head, ft_substr(c->value, i, j), WORD);
					if (!ka_u_redir_pipe_chi(c->value[i + j]))
					{
						add_token(&head, get_operator(c->value, i+j, &k), WORD);
						i += k;
					}
					break;
				}
			}
			i += j;
		}
		tmp = c->next;
		free_tok(c);
		c = tmp;
	}
	*first = head;
}
