/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:04:03 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

void	init_tokens(char *line, t_data *data_base)
{
	int		i;
	t_token	*head = NULL;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		else if (line[i] == '|')
		{
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
}
