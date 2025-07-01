/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:28 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/01 18:17:20 by miaghabe         ###   ########.fr       */
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

// void    free_cmd(t_cmd **cmd)
// {
//     t_cmd    *current;
//     t_cmd    *next;

//     if (cmd == NULL || *cmd == NULL)
//         return ;
//     current = *cmd;
//     while (current != NULL)
//     {
//         next = current-> next;
//         if (current->limiter != NULL)
//             free(current->limiter);
//         free(current->value);
//         current = next;
//     }
//     *cmd = NULL;
// }


void	free_tokens(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;
	t_cmd	cmd;

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
			print_tokens(data_base.token);
			if (check_syntax_errors(data_base.token))
				return (1);
			cmd.args = ft_split(line, ' ');
			cmd.next = NULL;
			if (is_builtin(cmd.args[0]))
				execute_builtin(&cmd, &data_base);
			else
				printf("not a built-in command\n");
			free_array(cmd.args);
			free_tokens(data_base.token); // esi nora
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
