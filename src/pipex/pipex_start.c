/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:50:16 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 17:37:02 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void free_lim(t_limiter **cmd)
{
	t_limiter *tmp;
	t_limiter *next;

	if (!cmd || !*cmd)
		return;
	tmp = *cmd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*cmd = NULL;
}

void	add_lim(t_limiter **head, char *value)
{
	t_limiter *new = malloc(sizeof(t_limiter));
	new->value = value;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
	{
		t_limiter *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void no_pipe(t_pipex *pipex, t_data *data_base)
{
	int inf = 0 ;
	int out = 1;
	
	if (pipex->infile != 0)
		inf = dup(0);
	if (pipex->outfile != 1)
		out = dup(1);
	if (is_builtin(pipex->cmd[0]))
	{
		pipex->pid[pipex->current_cmd]= 0;
		if (pipex->infile != 0)
		{
			dup2(pipex->infile, STDIN_FILENO);
			close(pipex->infile);
		}
		if (pipex->outfile != 1)
		{
			dup2(pipex->outfile, STDOUT_FILENO);
			close(pipex->outfile);
		}
		execute_builtin(pipex->cmd, data_base);
		if (inf != 0)
		{	
			dup2(inf, STDIN_FILENO);
			close(inf);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pipex->pid[pipex->forks] = fork();
	if (pipex->pid[pipex->forks] == -1)
	{
		g_err_no = 1;
		ft_putstr_fd("Error forking\n", 2);
		return ;
	}
	if (pipex->pid[pipex->forks] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pipex->limiter)
			read_here_doc(pipex, pipex->limiter, data_base);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		if (pipex->infile != 0)
			close(pipex->infile);
		if (pipex->outfile != 1)
			close(pipex->outfile);
		execute_cmd(pipex);
	}
	pipex->forks++;
	if (pipex->infile != 0)
		close(pipex->infile);
	if (pipex->outfile != 1)
		close(pipex->outfile);
}

void free_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	t_cmd *next;

	if (!cmd || !*cmd)
		return;
	tmp = *cmd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
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
		{
			if (access(cpy->value, F_OK) == -1)
			{
				ft_putstr_fd(cpy->value, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_err_no = 1;
				return ;
			}
			else if (access(cpy->value, R_OK) == -1)
			{
				ft_putstr_fd(cpy->value, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				g_err_no = 1;
				return ;
			}
			pipex->infile = open(cpy->value, O_RDONLY);
			if (pipex->infile == -1)
			{
				ft_putstr_fd(cpy->value, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_err_no = 1;
				return ;
			}
		}
		else if (cpy->type == OUTFILE || cpy->type == OUTFILE_APPEND)
		{
			if (access(cpy->value, F_OK) != -1 && access(cpy->value, W_OK) == -1)
			{
				ft_putstr_fd(cpy->value, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				g_err_no = 1;
				return ;
			}
			if (cpy->type == OUTFILE_APPEND)
				pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
			else
				pipex->outfile = open(cpy->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		else if (cpy->type == LIMITER)
			add_lim(&pipex->limiter, ft_strdup(cpy->value));
		cpy = cpy->next;
	}
}

void	free_struct(t_pipex *pipex)
{
	if (!pipex)
		return;
	free_double(pipex->path);
	free(pipex->pid);
	free_lim(&pipex->limiter);
}

void	pipex_start(t_data *db, t_token *token)
{
	t_token	*cpy;
	t_pipex	pipex;
	t_cmd	*cmd;
	char	*tmp;
	char	*cmd_line;
	int		i;
	int		count;
	int		status;

	cmd = NULL;
	cpy = token;
	init(db, &pipex);
	while (pipex.current_cmd < pipex.count_cmd)
	{
		if (!cpy)
			return ;
		cmd_line = ft_strdup("");
		while (cpy && cpy->type != S_PIPE)
		{
			if (cpy->type == WORD)
			{
				tmp = cmd_line;
				cmd_line = ft_strsjoin(cmd_line, cpy->value, 31);
				free(tmp);
			}
			add_cmd(&cmd, ft_strdup(cpy->value), cpy->type);
			cpy = cpy->next;
		}
		if (cpy)
			cpy = cpy->next;
		pipex.cmd = ft_split(cmd_line, 31);
		free(cmd_line);
		commands(cmd, &pipex);
		if (g_err_no != 0)
		{
			free_cmd(&cmd);
			free_double(pipex.cmd);
			free_struct(&pipex);
			return ;
		}
		if (db->pipes_count == 0)
			no_pipe(&pipex, db);
		else if (pipex.current_cmd == 0)
			first(&pipex, db);
		else if (pipex.current_cmd == pipex.count_cmd - 1)
			last(&pipex, db);
		else
			mid(&pipex, db);
		free_cmd(&cmd);
		free_double(pipex.cmd);
		pipex.cmd = NULL;
		(pipex.current_cmd)++;
	}
	i = 0;
	count = 0;
	while (i < pipex.forks)
	{
		waitpid(pipex.pid[i++], &status, 0);
		if (WIFEXITED(status))
			g_err_no = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !count)
			{
				count = 1;
				write(STDOUT_FILENO, "\n", 1);
			}
			if (WTERMSIG(status) == SIGQUIT && !count)
			{
				count = 1;
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			}
			g_err_no = 128 + WTERMSIG(status);
		}
	}
	free_struct(&pipex);
}
