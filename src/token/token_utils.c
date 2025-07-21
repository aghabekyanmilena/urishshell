/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:23:25 by anush             #+#    #+#             */
/*   Updated: 2025/07/22 00:23:27 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	free_tok(t_token *c)
{
	free(c->value);
	free(c);
}

int	limiter_for_dollar(char c)
{
	if (c && !ft_isspace(c) && c != '~'
		&& c != '@' && c != '#' && c != '$'
		&& c != '%' && c != '^' && c != '-'
		&& c != '+' && c != '=' && c != '/'
		&& c != '.' && c != ':' && c != '!'
		&& c != '"' && c != '\'' && c != '\n')
		return (1);
	return (0);
}

char	*return_bacac(char *line, int *i, int k, t_data *db)
{
	char	*free_anel;
	char	*doll;
	char	*bacac;

	doll = NULL;
	bacac = NULL;
	free_anel = ft_substr(line, *i, k);
	if (ft_strcmp(free_anel, "?") == 0)
	{
		doll = ft_itoa(g_err_no);
		bacac = ft_strdup(doll);
		free(doll);
	}
	else
		bacac = ft_strdup(get_env(db->env, free_anel));
	free(free_anel);
	if (!bacac)
		bacac = ft_strdup("");
	return (bacac);
}

char	*ft_join_3(char *start, char *mid, char *end)
{
	char	*str;
	int		i;
	int		j;

	if (!start || !mid || !end)
		return (NULL);
	str = (char *)malloc((ft_strlen(start) + ft_strlen(mid)
				+ ft_strlen(end) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (start[i])
		str[i++] = start[j++];
	j = 0;
	while (mid[j])
		str[i++] = mid[j++];
	j = 0;
	while (end[j])
		str[i++] = end[j++];
	str[i] = '\0';
	free(start);
	free(mid);
	free(end);
	return (str);
}

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

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
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
