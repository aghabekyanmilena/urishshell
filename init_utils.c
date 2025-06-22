/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:56:45 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/22 23:21:17 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/tokenization.h"
#include <string.h>

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

	while (line[*i] && !isspace(line[*i])
		&& line[*i] != '|' && line[*i] != '&'
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '"' && line[*i] != '\'')
		(*i)++;
	return (strndup(&line[start], *i - start));
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
	char *result = strndup(&line[start], *i - start);
	if (line[*i] == quote)
		(*i)++;
	return result;
}
