/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 00:18:18 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	redirnery(t_data *db)
{
	t_token *cpy;
	t_token *prev;


	prev = data_base->token;
	cpy = prev->next;
	while (cpy)
	{
		if (ft_strncmp(cpy->value, "<<", 2) == 0)
		{
			//write new function to add inside the tokens
		}
		cpy = cpy->next;
	}
	
}

char *get_env(char **env, const char *key)
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

void	chakert_hanel(t_data *db)
{
	t_token	*cpy;
	char	*before;
	char	*after;
	char	*inside;
	char	quote;
	int		i;
	int		j;

	cpy = db->token;
	before = NULL;
	while (cpy)
	{
		i = 0;
		while (cpy->value[i] != '\0')
		{
			j = 0;
			if (cpy->value[i] == '"' || cpy->value[i] == '\'')
			{
				quote = cpy->value[i];
				i++;
				while (cpy->value[i + j] && cpy->value[i + j] != quote)
					j++;
				if (i != 0)
					before = ft_substr(cpy->value, 0, i - 1);
				inside = ft_substr(cpy->value, i, j);
				after = ft_strjoin(before, inside);
				free(before);
				free(inside);
				inside = ft_substr(cpy->value, i + j + 1, ft_strlen(cpy->value) - i - j + 1);
				before = ft_strjoin(after, inside);
				free(inside);
				free(after);
				i += j - 1;
				free(cpy->value);
				cpy->value = ft_strdup(before);
				free(before);
			}
			else
				i++;
			
		}
		cpy = cpy->next;
	}
	
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

void	init_tokens_sharunak(t_data *data_base)
{
	t_token *cpy;

	cpy = data_base->token;
	data_base->pipes_count = 0;
	while (cpy)
	{
		if (ft_strcmp(cpy->value, "|") == 0)
		{
			if (cpy->next)
				cpy->type = S_PIPE;
			else
				return;
				// error
			(data_base->pipes_count)++;
		}
		else if (ft_strcmp(cpy->value, "<") == 0)
		{
			cpy->type = REDIR_OUT;
			if (cpy->next)
				cpy->next->type = INFILE;
			else
				return;
				// error
		}
		else if (ft_strcmp(cpy->value, "<<") == 0)
		{
			cpy->type = HEREDOC;
			if (cpy->next)
				cpy->next->type = LIMITER;
			else
				return;
				// error
		}
		else if (ft_strcmp(cpy->value, ">") == 0)
		{
			cpy->type = REDIR_OUT;
			if (cpy->next)
				cpy->next->type = OUTFILE;
			else
				return;
				// error
		}
		else if (ft_strcmp(cpy->value, ">>") == 0)
		{
			cpy->type = APPEND;
			if (cpy->next)
				cpy->next->type = OUTFILE_APPEND;
			else
				return;
				// error
		}
		cpy = cpy->next;
	}
}

void	chakert_check(char *line, t_data *data_base)
{
	int		i;
	int		j;
	char	*all;
	char	*new_line;
	t_token	*head = NULL;

	i = 0;
	all = ft_strdup(line);
	i = 0;
	
	while (all[i])
	{
		j = 0;
		while (ft_isspace(all[i]))
			i++;
		if (all[i] == '\0')
			break ;
		while (all[i + j] && !ft_isspace(all[i + j]))
		{
			if (all[i + j] == '"')
			{
				j++;
				while (all[i + j] && all[i + j] != '"')
					j++;
				if (all[i + j] != '"')
					return;
					//error
			}
			else if (all[i + j] == '\'')
			{
				j++;
				while (all[i + j] && all[i + j] != '\'')
					j++;
				if (all[i + j] != '\'')
					return;
					//error
			}
			j++;
			if  (!all[i + j] || ft_isspace(all[i + j]))
			{
				new_line = ft_substr(all, i, j);
				add_token(&head, new_line, WORD);
			}
		}
		i += j;
	}
	data_base->token = head;
}

void	init_tokens(char *line, t_data *data_base)
{
	chakert_check(line, data_base);
	dollar_bacel(data_base);
	chakert_hanel(data_base);
	redirnery(data_base);
	init_tokens_sharunak(data_base);
}
