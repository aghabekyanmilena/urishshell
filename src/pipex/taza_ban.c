/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taza_ban.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:50:16 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/01 19:03:28 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void no_pipe(t_pipex *pipex, t_data *data_base)
{
	pipex->pid[pipex->current_cmd] = fork();
	// if (pipex->pid[pipex->current_cmd] == -1)
	// 	err_exit("Error forking\n", pipex, 1);
	if (pipex->pid[pipex->current_cmd] == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		if (pipex->infile != 0)
			close(pipex->infile);
		if (pipex->outfile != 1)
			close(pipex->outfile);
		if (is_builtin(pipex->cmd[0]))
		{
			execute_builtin(pipex->cmd, data_base);
			exit(0);
		}
		else
			execute_cmd(pipex);
	}
	if (pipex->infile != 0)
		close(pipex->infile);
	if (pipex->outfile != 1)
		close(pipex->outfile);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (cmd == NULL || *cmd == NULL)
		return ;
	current = *cmd;
	while (current != NULL)
	{
		next = current-> next;
		free(current->value);
		current = next;
	}
	*cmd = NULL;
}

void	commands(t_cmd *cmd, t_pipex *pipex)
{
	t_cmd *cpy;

	cpy = cmd;
	pipex->infile = 0;
	pipex->outfile = 1;
	while (cpy)
	{
		if (cpy->type == INFILE)
			pipex->infile = open(cpy->value, O_RDONLY);
		else if (cpy->type == OUTFILE)
			pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (cpy->type == OUTFILE_APPEND)
			pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (cpy->type == LIMITER)
			pipex->limiter = ft_strdup(cpy->value);
		cpy = cpy->next;
	}
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
		if (cpy)
			cpy = cpy->next;
		pipex.cmd = ft_split(cmd_line, ' ');
		commands(cmd, &pipex);
		if (pipex.limiter != NULL)
			read_here_doc(&pipex, pipex.limiter);
		if (db->pipes_count == 0)
			no_pipe(&pipex, db);
		else if (pipex.current_cmd == 0)
			first(&pipex, db);
		else if (pipex.current_cmd == pipex.count_cmd - 1)
			last(&pipex, db);
		else
			mid(&pipex, db);
		if (pipex.limiter != NULL)
			unlink(TMP_FILE);
		free(cmd_line);
		free_cmd(&cmd);
		free_double(pipex.cmd);
		(pipex.current_cmd)++;
	}
	i = 0;
	while (i < pipex.count_cmd)
		waitpid(pipex.pid[i++], &status, 0);
	free_double(pipex.path);
	free(pipex.pid);
}
