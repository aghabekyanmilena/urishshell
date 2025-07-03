/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:35:42 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 16:20:58 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"
#include "../includes/built_in.h"
#include "../includes/signals.h"

void handle_shlvl(t_data *data);
char *get_env(char **env, const char *key);
void update_env(t_data *data, const char *key, const char *value);

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

char **copy_env(char **envp)
{
	int i = 0;
	while (envp[i])
		i++;

	char **copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	for (int j = 0; j < i; j++)
		copy[j] = ft_strdup(envp[j]);
	copy[i] = NULL;
	return copy;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;

	(void)argc;
	(void)argv;

	// data_base.env = env;
	data_base.env = copy_env(env);
	handle_shlvl(&data_base);

	while (1)
	{
		init_signal();
		line = readline("minishell: ");
		if (!line)
			break; // esi henc ctrl+D a, petqa senc lini
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base);
			// print_tokens(data_base.token);
			if (check_syntax_errors(data_base.token))
				return (1);
			pipex_start(&data_base, data_base.token);
			free_tokens(data_base.token); // esi nora
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
