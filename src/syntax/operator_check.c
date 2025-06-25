/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:04:53 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/25 16:00:32 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/syntax.h"

bool	is_operator(t_token_type type)
{
	return (type == S_PIPE || type == D_PIPE
			|| type == S_AND || type == D_AND);
}

bool	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
			|| type == HEREDOC || type == APPEND);
}
