/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/20 17:03:31 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		tokenize(line);
		free(line);
	}
	return (0);
}
