/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:28 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/30 15:10:05 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"
#include "../includes/syntax.h"

void	add_cmd(t_cmd **head, char *value, t_token_type type)
{
	t_cmd *new = malloc(sizeof(t_cmd));
	new->value = value;
	new->type = type;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
	{
		t_cmd *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void no_pipe(t_pipex *pipex)
{
	pipex->pid[pipex->current_cmd] = fork();
	// if (pipex->pid[pipex->current_cmd] == -1)
	// 	err_exit("Error forking\n", pipex, 1);
	if (pipex->pid[pipex->current_cmd] == 0)
	{
		execute_cmd(pipex);
	}
}

void	commands(t_cmd *cmd, t_pipex *pipex)
{
	t_cmd *cpy;

	cpy = cmd;
	while (cpy && cpy->type != INFILE)
		cpy = cpy->next;
	if (cpy && cpy->type == INFILE)
		pipex->infile = open(cpy->value, O_RDONLY);
	else
		pipex->infile = 0;
	cpy = cmd;
	while (cpy && cpy->type != OUTFILE && cpy->type != OUTFILE_APPEND)
		cpy = cpy->next;
	if (cpy && cpy->type == OUTFILE)
		pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (cpy && cpy->type == OUTFILE_APPEND)
		pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipex->outfile = 1;

}

void	pipex_start(t_data *db, t_token *token)
{
	t_token	*cpy;
	t_pipex	pipex;
	t_cmd	*cmd;
	int		i;
	int		status;

	cmd = NULL;
	cpy = token;
	init(db, &pipex);
	while (pipex.current_cmd < pipex.count_cmd)
	{
		if (cpy == NULL)
			return ;
		char *cmd_line = ft_strdup("");
		while (cpy && cpy->type != S_PIPE)
		{
			if (cpy->type == WORD)
			{
				char *tmp = cmd_line;
				cmd_line = ft_strsjoin(cmd_line, cpy->value, ' ');
				free(tmp);
			}
			add_cmd(&cmd, ft_strdup(cpy->value), cpy->type);
			cpy = cpy->next;
		}
		printf("%s\n", cmd_line);
		if (cpy)
			cpy = cpy->next;
		pipex.cmd = ft_split(cmd_line, ' ');
		commands(cmd, &pipex);
		if (db->pipes_count == 0)
			no_pipe(&pipex);
		else if (pipex.current_cmd == 0 && db->pipes_count != 0)
			first(&pipex);
		else if (pipex.current_cmd == pipex.count_cmd - 1)
			last(&pipex);
		else
			mid(&pipex);
		free(cmd_line);
		free_double(pipex.cmd);
		(pipex.current_cmd)++;
	}
	i = 0;
	while (i < pipex.count_cmd)
		waitpid(pipex.pid[i++], &status, 0);
	free_double(pipex.path);
	free(pipex.pid);
}

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
	// (void)env;

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
			// if (data_base.pipes_count != 0)
			pipex_start(&data_base, data_base.token);
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
}
