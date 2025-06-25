/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:56:45 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/25 15:59:30 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token *new = malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*read_word(char *line, int *i)
{
	int	start = *i;

	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '|' && line[*i] != '&'
		&& line[*i] != '<' && line[*i] != '>')
		(*i)++;
	return (ft_strndup(&line[start], *i - start));
}

char	*read_quoted_string(char *line, int *i, char **env)
{
	char	quote;
	int		start;
	(void)env;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	char *result = ft_strndup(&line[start], *i - start);
	if (line[*i] == quote)
		(*i)++;
	return result;
}
