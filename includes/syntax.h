/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:16:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/25 15:30:09 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
#define SYNTAX_H

#include "tokenization.h"

bool	is_operator(t_token_type type);
bool	is_redir(t_token_type type);
bool	check_syntax_errors(t_token *tokens);

#endif