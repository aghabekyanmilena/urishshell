/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:35:42 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 21:25:26 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"
#include "../includes/built_in.h"
#include "../includes/signals.h"

void	handle_shlvl(t_data *data);
char	*get_env(char **env, const char *key);
void	update_env(t_data *data, const char *key, const char *value);

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
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_data *db)
{
	t_token	*tmp;
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

char	**copy_env(char **envp)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	j = -1;
	while (++j < i)
		copy[j] = ft_strdup(envp[j]);
	copy[i] = NULL;
	return (copy);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;

	(void)argc;
	(void)argv;
	data_base.env = copy_env(env);
	handle_shlvl(&data_base);
	while (1)
	{
		init_signal();
		line = readline("minishell: ");
		if (!line)
			break ;
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
