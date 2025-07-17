/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:35:42 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 19:11:29 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"
#include "../includes/built_in.h"
#include "../includes/signals.h"

int	g_err_no = 0;

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("Type: %d, Value: %s\n", tok->type, tok->value);
		tok = tok->next;
	}
}

void	free_tokens(t_data *db)
{
	t_token	*tmp;
	t_token	*head;

	head = db->token;
	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
	db->token = NULL;
}

char	**copy_env(char **envp)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	while (j < i)
	{
		copy[j] = ft_strdup(envp[j]);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

void	init_db_and_shlvl(t_data *db, char **env)
{
	g_err_no = 0;
	db->env = copy_env(env);
	db->command_count = 0;
	db->token = NULL;
	handle_shlvl(db);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;

	init_db_and_shlvl(&data_base, env);
	(void)argc;
	(void)argv;
	while (1)
	{
		init_signal();
		line = readline("urishshell: ");
		if (!line)
			break ;
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base);
			if (check_syntax_errors(&data_base) == 0)
				pipex_start(&data_base, data_base.token);
			free_tokens(&data_base);
			add_history(line);
		}
		free(line);
	}
	free_double(data_base.env);
	rl_clear_history();
	return (0);
}
