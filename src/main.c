/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:28 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/25 15:59:15 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;
	(void)argv;
	(void)argc;
	(void)env;

	while (1)
	{
		line = readline("enter command: ");
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base);
			// print_tokens(data_base.token);
			if (check_syntax_errors(data_base.token))
				return (1);
		}
		free(line);
	}
}
