/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:23:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/25 16:00:24 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/syntax.h"

static void	syntax_error(const char *token)
{
	printf("minishell: syntax error, unexpected token `%s'\n", token);
}

bool	check_syntax_errors(t_token *tokens)
{
	t_token	*curr = tokens;

	if (!curr)
		return (false);
	if (is_operator(curr->type))
	{
		syntax_error(curr->value);
		return (true);
	}
	while (curr && curr->next)
	{
		if (is_operator(curr->type) && is_operator(curr->next->type))
		{
			syntax_error(curr->next->value);
			return (true);
		}
		if (is_redir(curr->type)
			&& (is_operator(curr->next->type) || is_redir(curr->next->type)))
		{
			syntax_error(curr->next->value);
			return (true);
		}
		curr = curr->next;
	}
	if (is_operator(curr->type) || is_redir(curr->type))
	{
		syntax_error(curr->value);
		return (true);
	}
	return (false);
}
