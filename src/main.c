/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:35:42 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 13:56:08 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/tokenization.h"
#include "../includes/syntax.h"
#include "../includes/built_in.h"

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("Type: %d, Value: %s\n", tok->type, tok->value);
		tok = tok->next;
	}
}

void	free_array(char **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_data *db)
{
	t_token *tmp;
	t_token	*head;

	head = db->token;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
	db->token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;

	(void)argc;
	(void)argv;
	data_base.env = env;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break;
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base);
			if (check_syntax_errors(&data_base))
			{
				free(line);
				return (1);
			}
			print_tokens(data_base.token);
			pipex_start(&data_base, data_base.token);
			free_tokens(&data_base);
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
