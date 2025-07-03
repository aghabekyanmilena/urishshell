/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 19:24:57 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"


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
			if (cpy->value[i] == '$' && cpy->value[i + 1] != '\0')
			{
				i++;
				k = 0;
				while (cpy->value[i + k] != '\0' && !ft_isspace(cpy->value[i + k]) && cpy->value[i + k] != '~' \
					 && cpy->value[i + k] != '@' && cpy->value[i + k] != '#' && cpy->value[i + k] != '$' \
					 && cpy->value[i + k] != '%' && cpy->value[i + k] != '^' && cpy->value[i + k] != '-' \
					 && cpy->value[i + k] != '+' && cpy->value[i + k] != '=' && cpy->value[i + k] != '/' \
					 && cpy->value[i + k] != '.' && cpy->value[i + k] != ':' && cpy->value[i + k] != '!')
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
				// error
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
	
	// while (line[i])
	// {
		
		// while (ft_isspace(line[i]))
		// 	i++;
		// if (!line[i])
		// 	break ;
		// else if (line[i] == '|')
		// {
		// 	(data_base->pipes_count)++;
		// 	add_token(&head, ft_strdup("|"), S_PIPE);
		// 	i++;
		// }
		// else if (line[i] == '&')
		// {
		// 	add_token(&head, ft_strdup("&"), S_AND);
		// 	i++;
		// }
		// else if (line[i] == '>')
		// {
		// 	if (line[i + 1] == '>')
		// 	{
		// 		add_token(&head, ft_strdup(">>"), APPEND);
		// 		i++;
		// 	}
		// 	else
		// 		add_token(&head, ft_strdup(">"), REDIR_OUT);
		// 	i++;
		// }
		// else if (line[i] == '<')
		// {
		// 	if (line[i + 1] == '<')
		// 	{
		// 		add_token(&head, ft_strdup("<<"), HEREDOC);
		// 		i++;
		// 	}
		// 	else
		// 		add_token(&head, ft_strdup("<"), REDIR_IN);
		// 	i++;
		// }
		// else
		// 	add_token(&head, read_word(line, &i), WORD);
	// }
	// data_base->token = head;
	init_tokens_sharunak(data_base);
	dollar_bacel(data_base);
}
