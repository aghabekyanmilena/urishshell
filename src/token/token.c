/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/09 00:10:20 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"

void	redirnery(t_token **first)
{
	t_token	*start;
	t_token	*cpy;
	t_token	*tmp;
	char	*before;
	char	*after;
	char	*op;
	int		i;
	int		j;

	cpy = *first;
	start = NULL;
	op = NULL;
	while (cpy)
	{
		i = 0;
		j = 0;
		while (cpy->value[i] && cpy->value[i] != '<' && cpy->value[i] != '>' && cpy->value[i] != '|')
			i++;
		if (cpy->value[i])
		{
			if (cpy->value[i] == '<')
			{
				j++;
				op = ft_strdup("<");
				if (cpy->value[i + 1] == '<')
				{
					j++;
					free(op);
					op = ft_strdup("<<");
				}
			}
			else if (cpy->value[i] == '>')
			{
				j++;
				op = ft_strdup(">");
				if (cpy->value[i + 1] == '>')
				{
					j++;
					free(op);
					op = ft_strdup(">>");
				}
			}
			else if (cpy->value[i] == '|')
			{
				j++;
				op = ft_strdup("|");
			}
			if (i > 0)
			{
				before = ft_substr(cpy->value, 0, i);
				add_token(&start, ft_strdup(before), WORD);
				free(before);
			}
			add_token(&start, ft_strdup(op), WORD);
			free(op);
			if (cpy->value[i + j])
			{
				after = ft_substr(cpy->value, i + j, ft_strlen(cpy->value) - (i + j));
				add_token(&start, ft_strdup(after), WORD);
				free(after);
			}
		}
		else
			add_token(&start, ft_strdup(cpy->value), WORD);
		tmp = cpy->next;
		free(cpy->value);
		free(cpy);
		cpy = tmp;
	}
	*first = start;

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

void	init_tokens_sharunak(t_data *data_base)
{
	t_token *cpy;

	cpy = data_base->token;
	data_base->pipes_count = 0;
	while (cpy)
	{
		if (ft_strcmp(cpy->value, "|") == 0)
		{
			(data_base->pipes_count)++;
			cpy->type = S_PIPE;
		}
		else if (ft_strcmp(cpy->value, "<") == 0)
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
		cpy = cpy->next;
	}
}

void	chakert_check(char *line, t_data *data_base)
{
	int		i;
	int		j;
	char	*all;
	char	*new_line;
	t_token	*head;

	i = 0;
	head = NULL;
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
				{
					free_tokens(data_base);
					free(all);
					return;
				}	//error
			}
			else if (all[i + j] == '\'')
			{
				j++;
				while (all[i + j] && all[i + j] != '\'')
					j++;
				if (all[i + j] != '\'')
				{
					free_tokens(data_base);
					free(all);
					return;
				}
					//error
			}
			j++;
			if  (!all[i + j] || ft_isspace(all[i + j]))
			{
				new_line = ft_substr(all, i, j);
				add_token(&head, ft_strdup(new_line), WORD);
				free(new_line);
			}
		}
		i += j;
	}
	free(all);
	data_base->token = head;
}

char	*check_dollar(char *line, t_data *db, int *i)
{
	int		k;
	char	*bacac;
	char	*free_anel;
	char	*start;
	char	*end;
	char	*doll;
	char	*dup;

	dup = ft_strdup(line);
	doll = NULL;
	if (dup[*i] == '$' && dup[*i + 1] != '\0')
	{
		(*i)++;
		k = 0;
		if (dup[*i] != '?')
		{
			while (dup[*i + k] != '\0' && !ft_isspace(dup[*i + k]) && dup[*i + k] != '~' \
				&& dup[*i + k] != '@' && dup[*i + k] != '#' && dup[*i + k] != '$' \
				&& dup[*i + k] != '%' && dup[*i + k] != '^' && dup[*i + k] != '-' \
				&& dup[*i + k] != '+' && dup[*i + k] != '=' && dup[*i + k] != '/' \
				&& dup[*i + k] != '.' && dup[*i + k] != ':' && dup[*i + k] != '!' \
				&& dup[*i + k] != '"' && dup[*i + k] != '\'' && dup[*i + k] != '\n')
				k++;
		}
		else
			k++;
		free_anel = ft_substr(dup, *i, k);
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
		start = ft_substr(dup, 0, *i - 1);
		free(free_anel);
		free_anel = ft_strjoin(start, bacac);
		free(start);
		free(bacac);
		end = ft_substr(dup, *i + k, ft_strlen(dup) - *i - k);
		bacac = ft_strjoin(free_anel, end);
		free(free_anel);
		free(end);
		free(dup);
		dup = bacac;
		*i+=k;
	}
	else 
		(*i)++;
	return (dup);
}

char	*dollar_in_line(char *line, t_data *db)
{
	int		i;
	char	*new;
	i = 0;
	while(line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				new = check_dollar(line, db, &i);
		}
		else
		{
			while (line[i] && line[i] != '"' && line[i] != '\'')
				new = check_dollar(line, db, &i);
		}
	}
	return (new);
}

void	init_tokens(char *line, t_data *data_base)
{
	// char	*dup;

	// dup = dollar_in_line(line, data_base);
	//porcel flagov
	chakert_check(dup, data_base);
	// dollar_bacel(data_base);
	chakert_hanel(data_base);
	redirnery(&(data_base->token));
	init_tokens_sharunak(data_base);
	free(dup);
}
