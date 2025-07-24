/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:33:30 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/23 15:46:04 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd(t_pipex *pipex)
{
	int		j;
	char	*full_path;

	j = 0;
	if (!pipex->cmd)
		exit (0);
	if (ft_strncmp(pipex->cmd[0], "./", 2) == 0
		&& ft_strcmp(pipex->cmd[0] + ft_strlen(pipex->cmd[0]) - 4, ".out") != 0)
		bash_script(pipex);
	if (pipex->path != NULL)
	{
		while (pipex->path[j])
		{
			full_path = ft_strsjoin(pipex->path[j], pipex->cmd[0], '/');
			execve(full_path, pipex->cmd, pipex->env);
			free(full_path);
			j++;
		}
	}
	execve(pipex->cmd[0], pipex->cmd, pipex->env);
	g_err_no = 127;
	ft_putstr_fd(pipex->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(g_err_no);
}

void	duping_children(int fd1, int fd2, t_data *data_base, t_pipex *pipex)
{
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	if (fd1 != 0)
		close(fd1);
	if (fd2 != 1)
		close(fd2);
	if (!pipex->cmd)
		exit (0);
	if (is_builtin(pipex->cmd[0]))
	{
		execute_builtin(pipex->cmd, data_base);
		exit(g_err_no);
	}
	else
		execute_cmd(pipex);
}

void	mid(t_pipex *pipex, t_data *data_base, int fders[2])
{
	if (pipe(fders) == -1)
	{
		err_for_files("Error piping", "\n", data_base);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pipex->pid[pipex->forks] = fork();
	if (pipex->pid[pipex->forks] == -1)
	{
		closing_files(pipex);
		err_for_files("Error forking", "\n", data_base);
		return ;
	}
	if (pipex->pid[pipex->forks++] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pipex->limiter)
			read_here_doc(pipex, pipex->limiter, data_base);
		close(fders[0]);
		duping_children(pipex->fds[0], fders[1], data_base, pipex);
	}
	close(pipex->fds[0]);
	close(fders[1]);
	pipex->fds[0] = fders[0];
}

void	first(t_pipex *pipex, t_data *data_base)
{
	if (pipe(pipex->fds) == -1)
	{
		err_for_files("Error piping", "\n", data_base);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pipex->pid[pipex->forks] = fork();
	if (pipex->pid[pipex->forks] == -1)
	{
		closing_files(pipex);
		err_for_files("Error forking", "\n", data_base);
		return ;
	}
	if (pipex->pid[pipex->forks++] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pipex->limiter)
			read_here_doc(pipex, pipex->limiter, data_base);
		close(pipex->fds[0]);
		duping_children(pipex->infile, pipex->fds[1], data_base, pipex);
	}
	if (pipex->infile != 0)
		close(pipex->infile);
	close(pipex->fds[1]);
}

void	last(t_pipex *pipex, t_data *data_base)
{
	signal(SIGINT, SIG_IGN);
	pipex->pid[pipex->forks] = fork();
	if (pipex->pid[pipex->forks] == -1)
	{
		closing_files(pipex);
		err_for_files("Error forking", "\n", data_base);
		return ;
	}
	if (pipex->pid[pipex->forks++] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pipex->limiter)
			read_here_doc(pipex, pipex->limiter, data_base);
		duping_children(pipex->fds[0], pipex->outfile, data_base, pipex);
	}
	close(pipex->fds[0]);
	if (pipex->outfile != 1)
		close(pipex->outfile);
}
