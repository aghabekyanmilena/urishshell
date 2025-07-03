/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:04:53 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 19:29:30 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/syntax.h"

bool	is_operator(t_token_type type)
{
	return (type == S_PIPE);
}

bool	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
			|| type == HEREDOC || type == APPEND);
}
