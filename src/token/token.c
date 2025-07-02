/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/02 18:43:51 by atseruny         ###   ########.fr       */
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
				// printf("%s\n", bacac);
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
				// break;
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
		if (ft_strcmp(cpy->value, "<") == 0)
		{
			if (cpy->next)
				cpy->next->type = INFILE;
		}
		else if (ft_strcmp(cpy->value, "<<") == 0)
		{
			if (cpy->next)
				cpy->next->type = LIMITER;
		}
		else if (ft_strcmp(cpy->value, ">") == 0)
		{
			if (cpy->next)
				cpy->next->type = OUTFILE;
		}
		else if (ft_strcmp(cpy->value, ">>") == 0)
		{
			if (cpy->next)
				cpy->next->type = OUTFILE_APPEND;
		}
		cpy = cpy->next;
	}
}

void	init_tokens(char *line, t_data *data_base)
{
	int		i;
	t_token	*head = NULL;

	i = 0;
	data_base->pipes_count = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		else if (line[i] == '|')
		{
			(data_base->pipes_count)++;
			if (line[i + 1] == '|')
			{
				add_token(&head, ft_strdup("||"), D_PIPE);
				i+=2;
			}
			else
			{
				add_token(&head, ft_strdup("|"), S_PIPE);
				i++;
			}
		}
		else if (line[i] == '&')
		{
			if (line[i + 1] == '&')
			{
				add_token(&head, ft_strdup("&&"), D_AND);
				i+=2;
			}
			else
			{
				add_token(&head, ft_strdup("&"), S_AND);
				i++;
			}
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			add_token(&head, ft_strdup(">>"), APPEND);
			i += 2;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			add_token(&head, ft_strdup("<<"), HEREDOC);
			i += 2;
		}
		else if (line[i] == '>')
		{
			add_token(&head, ft_strdup(">"), REDIR_OUT);
			i++;
		}
		else if (line[i] == '<')
		{
			add_token(&head, ft_strdup("<"), REDIR_IN);
			i++;
		}
		else
			add_token(&head, read_word(line, &i), WORD);
	}
	data_base->token = head;
	init_tokens_sharunak(data_base);
	dollar_bacel(data_base);
}
