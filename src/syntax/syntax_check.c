/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:23:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 16:24:29 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/syntax.h"

bool	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}

void	syntax_error(t_data *db, char *token)
{
	g_err_no = 1;
	printf("syntax error: unexpected token `%s'\n", token);
	free_tokens(db);
}

void	check_pipe()
{
	
}

bool	check_syntax_errors(t_data *db)
{
	t_token	*curr;

	if (g_err_no == 1)
		return (true);
	curr = db->token;
	if (!curr)
		return (false);
	if (curr->type == S_PIPE)
	{
		syntax_error(db, curr->value);
		return (true);
	}
	while (curr->next)
	{
		if ((curr->type == S_PIPE
			&& (curr->next->type == S_PIPE || is_redir(curr->next->type)))
			|| (is_redir(curr->type) && (curr->next->type == S_PIPE
			|| is_redir(curr->next->type))))
		{
			syntax_error(db, curr->next->value);
			return (true);
		}
		curr = curr->next;
	}
	if (curr->type == S_PIPE || is_redir(curr->type))
	{
		syntax_error(db, curr->value);
		return (true);
	}
	g_err_no = 0;
	return (false);
}
