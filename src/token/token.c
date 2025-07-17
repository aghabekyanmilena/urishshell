/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 19:56:24 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"

void	chakert_hanel(t_token *c, char *before, int i, int j)
{
	char	quote;

	while (c)
	{
		i = 0;
		while (c->value[i] != '\0')
		{
			j = 0;
			if (c->value[i] == '"' || c->value[i] == '\'')
			{
				quote = c->value[i++];
				while (c->value[i + j] && c->value[i + j] != quote)
					j++;
				before = ft_join_3(ft_substr(c->value, 0, i - 1),
						ft_substr(c->value, i, j),
						ft_substr(c->value, i + j + 1, ft_strlen(c->value) - i - j + 1));
				free(c->value);
				c->value = before;
				i += j - 1;
			}
			else
				i++;
		}
		c = c->next;
	}
}

void	chakert_check(char *all, t_data *data_base, int i, t_token *head)
{
	int		j;
	char	chak;

	g_err_no = 0;
	while (all[i])
	{
		j = 0;
		while (ft_isspace(all[i]))
			i++;
		while (all[i + j] && !ft_isspace(all[i + j]))
		{
			if (all[i + j] == '"' || all[i + j] == '\'')
			{
				chak = all[i + j];
				j++;
				while (all[i + j] && all[i + j] != chak)
					j++;
				if (all[i + j] != chak)
				{
					syntax_error(data_base, all);
					break ;
				}
			}
			j++;
			if (!all[i + j] || ft_isspace(all[i + j]))
			{
				add_token(&head, ft_substr(all, i, j), WORD);
				data_base->token = head;
			}
		}
		i += j;
	}
}

char	*check_dollar(char *line, t_data *db, int *i, int f)
{
	int		k;
	char	*free_anel;

	while (line[*i] && ((line[*i] != '\'' && !f) || (line[*i] != '"' && f)))
	{
		if (line[*i] == '$' && line[*i + 1])
		{
			(*i)++;
			k = 0;
			if (line[*i] != '?' && line[*i + 1])
				while (limiter_for_dollar(line[*i + k]))
					k++;
			else
				k++;
			free_anel = ft_join_3(ft_substr(line, 0, *i - 1),
					return_bacac(line, i, k, db),
					ft_substr(line, *i + k, ft_strlen(line) - *i - k));
			free(line);
			line = free_anel;
			(*i)--;
		}
		else
			(*i)++;
	}
	return (line);
}

char	*dollar_in_line(char *line, t_data *db)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup(line);
	while (new[i])
	{
		if (new[i] == '\'')
		{
			i++;
			while (new[i] && new[i] != '\'')
				i++;
		}
		else if (new[i] == '"' && new[i + 1])
		{
			i++;
			new = check_dollar(new, db, &i, 1);
		}
		else
			new = check_dollar(new, db, &i, 0);
	}
	return (new);
}

void	init_tokens(char *line, t_data *data_base)
{
	char	*dup;

	dup = dollar_in_line(line, data_base);
	chakert_check(dup, data_base, 0, NULL);
	chakert_hanel(data_base->token, NULL, 0, 0);
	redirnery(&(data_base->token), data_base->token, NULL, 0);
	init_tokens_sharunak(data_base, data_base->token);
	(data_base->command_count)++;
	free(dup);
}
