/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:50:22 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/23 00:03:39 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	no_pipe_builtin(t_pipex *pipex, t_data *data_base, int inf, int out)
{
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
}

int	no_pipe_wo_fork(t_pipex *pipex, t_data *data_base, int inf, int out)
{
	if (pipex->limiter)
		read_here_doc(pipex, pipex->limiter, data_base);
	if (pipex->infile != 0)
		inf = dup(STDIN_FILENO);
	if (pipex->outfile != 1)
		out = dup(STDOUT_FILENO);
	if (pipex->cmd && is_builtin(pipex->cmd[0]))
		return (no_pipe_builtin(pipex, data_base, inf, out), 1);
	if (inf != -1 && inf != STDIN_FILENO)
		close(inf);
	if (out != 1 && out != STDOUT_FILENO)
		close(out);
	return (0);
}

void	no_pipe(t_pipex *pipex, t_data *data_base)
{
	if (no_pipe_wo_fork(pipex, data_base, 0, 1))
		return ;
	signal(SIGINT, SIG_IGN);
	pipex->pid[pipex->forks] = fork();
	if (pipex->pid[pipex->forks] == -1)
	{
		err_for_files("Error forking", "\n", data_base);
		return ;
	}
	if (pipex->pid[pipex->forks++] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		closing_files(pipex);
		execute_cmd(pipex);
	}
	closing_files(pipex);
}
