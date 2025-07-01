/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_anush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:28 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/01 18:52:23 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("Type: %d, Value: %s\n", tok->type, tok->value);
		tok = tok->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;
	(void)argv;
	(void)argc;

	data_base.env = env;
	while (1)
	{
		line = readline("minishell: ");
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base);
			print_tokens(data_base.token);
			if (check_syntax_errors(data_base.token))
				return (1);
			pipex_start(&data_base, data_base.token);
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
}
