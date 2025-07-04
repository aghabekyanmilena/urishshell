/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:16:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 20:50:40 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "tokenization.h"

void	free_tokens(t_data *db);
void	syntax_error(t_data *db, t_token *token);
bool	is_redir(t_token_type type);
bool	check_syntax_errors(t_data *db);

#endif