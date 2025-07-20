/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:01:23 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/20 16:54:16 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	bash_script(t_pipex *pipex)
{
	if (access(pipex->cmd[0], F_OK | X_OK) == 0)
		execve(pipex->cmd[0], pipex->cmd, pipex->env);
	g_err_no = 127;
	ft_putstr_fd(pipex->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	waiting_for_childs(t_pipex *pipex, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->forks)
	{
		waitpid(pipex->pid[i++], &status, 0);
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
	free_struct(pipex);
}

int	start_executing(t_data *db, t_pipex *pipex)
{
	int	fders[2];

	if (db->for_syntax_err != 0)
	{
		free_double(pipex->cmd);
		pipex->cmd = NULL;
		free_lim(&pipex->limiter);
		pipex->limiter = NULL;
		return (1);
	}
	if (db->pipes_count == 0)
		no_pipe(pipex, db);
	else if (pipex->current_cmd == 0)
		first(pipex, db);
	else if (pipex->current_cmd == pipex->count_cmd - 1)
		last(pipex, db);
	else
		mid(pipex, db, fders);
	free_double(pipex->cmd);
	pipex->cmd = NULL;
	free_lim(&pipex->limiter);
	pipex->limiter = NULL;
	(pipex->current_cmd)++;
	return (0);
}

char	*get_cmd_line(t_token *cpy, char *cmd_line)
{
	char	*tmp;

	tmp = cmd_line;
	cmd_line = ft_strsjoin(cmd_line, cpy->value, 31);
	free(tmp);
	return (cmd_line);
}

void	pipex_start(t_data *db, t_token *cpy, t_token *cmd)
{
	t_pipex	pipex;
	char	*cmd_line;

	init(db, &pipex);
	while (cpy && pipex.current_cmd < pipex.count_cmd) // && !g_err_no
	{
		cmd_line = ft_strdup("");
		while (cpy && cpy->type != S_PIPE)
		{
			if (cpy->type == WORD)
				cmd_line = get_cmd_line(cpy, cmd_line);
			add_token(&cmd, ft_strdup(cpy->value), cpy->type);
			cpy = cpy->next;
		}
		if (cpy)
			cpy = cpy->next;
		pipex.cmd = ft_split(cmd_line, 31);
		free(cmd_line);
		commands(cmd, &pipex, db);
		free_cmd(&cmd);
		if (start_executing(db, &pipex))
			break ;
	}
	waiting_for_childs(&pipex, 0);
}
