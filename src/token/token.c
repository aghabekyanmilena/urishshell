/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 20:42:42 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	chakert_hanel(t_data *db)
{
	t_token	*cpy;
	char	*value;
	char	*before;
	char	*after;
	char	*inside;
	int		i;
	int		j;

	cpy = db->token;
	before = ft_strdup("");
	while (cpy)
	{
		i = 0;
		value = cpy->value;
		while (value[i])
		{
			if (value[i] == '"' && value[i + 1])
			{
				i++;
				j = 0;
				while (value[i + j] && value[i + j] != '"')
					j++;
				free(before);
				before = ft_substr(value, 0, i - 1);
				inside = ft_substr(value, i, j);
				after = ft_strjoin(before, inside);
				free(before);
				free(inside);
				inside = ft_substr(value, i + j + 1, ft_strlen(value) - i - j - 2);
				before = ft_strjoin(after, inside);
				free(inside);
				free(after);
				i += j - 1;
				free(cpy->value);
				cpy->value = ft_strdup(before);
			}
			else if (value[i] == '\'')
			{
				i++;
				j = 0;
				while (value[i + j] && value[i + j] != '\'')
					j++;
				free(before);
				before = ft_substr(value, 0, i - 1);
				inside = ft_substr(value, i, j);
				after = ft_strjoin(before, inside);
				free(before);
				free(inside);
				inside = ft_substr(value, i + j + 1, ft_strlen(value) - i - j - 2);
				before = ft_strjoin(after, inside);
				free(inside);
				free(after);
				i += j - 1;
				free(cpy->value);
				cpy->value = ft_strdup(before);
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
				bacac = ft_strdup(getenv(free_anel));
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
			i++;;
		}
		cpy = cpy->next;
	}
}

void	init_tokens_sharunak(t_data *data_base)
{
	t_token *cpy;

	cpy = data_base->token;
	while (cpy)
	{
		if (ft_strcmp(cpy->value, "|") == 0)
		{
			if (cpy->next)
				cpy->type = S_PIPE;
			else
				return;
			(data_base->pipes_count)++; // error
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
	int		i;

	i = 0;
	chakert_check(line, data_base);
	data_base->pipes_count = 0;
	init_tokens_sharunak(data_base);
	dollar_bacel(data_base);
	chakert_hanel(data_base);
}
