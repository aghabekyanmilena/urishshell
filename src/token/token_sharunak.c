/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sharunak.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:57:22 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/22 17:12:17 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/syntax.h"

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

char	*get_line(char *line, t_data *db, int *i, int k)
{
	char	*all;

	all = ft_join_3(ft_substr(line, 0, *i - 1), return_bacac(line, i, k, db),
			ft_substr(line, *i + k, ft_strlen(line) - *i - k));
	free(line);
	(*i)--;
	return (all);
}

int	chakert_check_sharunak(char *all, int *i, int *j, t_data *data_base)
{
	char	chak;

	if (all[*i + *j] == '"' || all[*i + *j] == '\'')
	{
		chak = all[*i + *j];
		(*j)++;
		while (all[*i + *j] && all[*i + *j] != chak)
			(*j)++;
		if (all[*i + *j] != chak)
			return (syntax_error(data_base, all), 1);
	}
	return (0);
}
