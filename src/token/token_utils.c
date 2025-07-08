/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:56:45 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 14:52:57 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	check_dollar_existance(t_token *cpy, t_data *db, int *i)
{
	int		k;
	char	*bacac;
	char	*free_anel;
	char	*start;
	char	*end;
	char	*doll;

	doll = NULL;
	if (cpy->value[*i] == '$' && cpy->value[*i + 1] != '\0')
	{
		(*i)++;
		k = 0;
		while (cpy->value[*i + k] != '\0' && !ft_isspace(cpy->value[*i + k]) && cpy->value[*i + k] != '~' \
			&& cpy->value[*i + k] != '@' && cpy->value[*i + k] != '#' && cpy->value[*i + k] != '$' \
			&& cpy->value[*i + k] != '%' && cpy->value[*i + k] != '^' && cpy->value[*i + k] != '-' \
			&& cpy->value[*i + k] != '+' && cpy->value[*i + k] != '=' && cpy->value[*i + k] != '/' \
			&& cpy->value[*i + k] != '.' && cpy->value[*i + k] != ':' && cpy->value[*i + k] != '!' \
			&& cpy->value[*i + k] != '"' && cpy->value[*i + k] != '\'')
			k++;
		free_anel = ft_substr(cpy->value, *i, k);
		bacac = ft_strdup(get_env(db->env, free_anel));
		if (!bacac)
		{
			if (ft_strcmp(free_anel, "?") == 0)
			{
				doll = ft_itoa(ERR_NO);
				bacac = ft_strdup(doll);
				free(doll);
			}
			else
				bacac = ft_strdup("");
		}
		start = ft_substr(cpy->value, 0, *i - 1);
		free(free_anel);
		free_anel = ft_strjoin(start, bacac);
		free(start);
		free(bacac);
		end = ft_substr(cpy->value, *i + k, ft_strlen(cpy->value) - *i - k);
		bacac = ft_strjoin(free_anel, end);
		free(free_anel);
		free(end);
		free(cpy->value);
		cpy->value = bacac;
	}
	else 
		(*i)++;
}

void	dollar_bacel(t_data *db)
{
	t_token	*cpy;
	int		i;

	cpy = db->token;
	while (cpy)
	{
		i = 0;
		while (cpy->value[i])
		{
			if (cpy->value[i] == '\'')
			{
				i++;
				while (cpy->value[i] && cpy->value[i] != '\'')
					i++;
			}
			else if (cpy->value[i] == '"')
			{
				i++;
				while (cpy->value[i] && cpy->value[i] != '"')
					check_dollar_existance(cpy, db, &i);
			}
			else
			{
				while (cpy->value[i])
					check_dollar_existance(cpy, db, &i);
			}
			
		}
		cpy = cpy->next;
	}
}

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
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
