/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:56:45 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 13:54:18 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

char	*get_env(char **env, const char *key)
{
	size_t len = ft_strlen(key);
	int	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return env[i] + len + 1;
		i++;
	}
	return (NULL);
}

void	dollar_bacel(t_data *db)
{
	t_token	*cpy;
	int		i;
	int		k;
	char	*bacac;
	char	*free_anel;
	char	*start;
	char	*end;

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
			if (cpy->value[i] == '$' && cpy->value[i + 1] != '\0')
			{
				i++;
				k = 0;
				while (cpy->value[i + k] != '\0' && !ft_isspace(cpy->value[i + k]) && cpy->value[i + k] != '~' \
					 && cpy->value[i + k] != '@' && cpy->value[i + k] != '#' && cpy->value[i + k] != '$' \
					 && cpy->value[i + k] != '%' && cpy->value[i + k] != '^' && cpy->value[i + k] != '-' \
					 && cpy->value[i + k] != '+' && cpy->value[i + k] != '=' && cpy->value[i + k] != '/' \
					 && cpy->value[i + k] != '.' && cpy->value[i + k] != ':' && cpy->value[i + k] != '!' \
					 && cpy->value[i + k] != '"' && cpy->value[i + k] != '\'')
					k++;
				free_anel = ft_substr(cpy->value, i, k);
				bacac = ft_strdup(get_env(db->env, free_anel));
				if (!bacac)
					bacac = ft_strdup("");
				start = ft_substr(cpy->value, 0, i - 1);
				free(free_anel);
				free_anel = ft_strjoin(start, bacac);
				free(start);
				free(bacac);
				end = ft_substr(cpy->value, i + k, ft_strlen(cpy->value) - i - k);
				bacac = ft_strjoin(free_anel, end);
				free(free_anel);
				free(end);
				free(cpy->value);
				cpy->value = bacac;
			}
			i++;
		}
		cpy = cpy->next;
	}
}

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token *new = malloc(sizeof(t_token));
	if (!new)
		return;
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
