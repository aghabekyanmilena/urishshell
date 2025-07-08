/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:23:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 14:22:29 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/syntax.h"

bool	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}

void	syntax_error(t_data *db, t_token *token)
{
	ERR_NO = 1;
	printf("minishell: syntax error, unexpected token `%s'\n", token->value);
	free_tokens(db);
}

bool	check_syntax_errors(t_data *db)
{
	t_token	*curr;

	curr = db->token;
	if (!curr)
		return (false);
	if (curr->type == S_PIPE)
	{
		syntax_error(db, curr);
		return (true);
	}
	while (curr->next)
	{
		if ((curr->type == S_PIPE
			&& (curr->next->type == S_PIPE || is_redir(curr->next->type)))
			|| (is_redir(curr->type) && (curr->next->type == S_PIPE
			|| is_redir(curr->next->type))))
		{
			syntax_error(db, curr->next);
			return (true);
		}
		curr = curr->next;
	}
	if (curr->type == S_PIPE || is_redir(curr->type))
	{
		syntax_error(db, curr);
		return (true);
	}
	ERR_NO = 0;
	return (false);
}
