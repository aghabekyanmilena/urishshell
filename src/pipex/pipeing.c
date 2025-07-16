/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:33:30 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/16 18:36:06 by atseruny         ###   ########.fr       */
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

void	execute_cmd(t_pipex *pipex)
{
	int		j;
	char	*full_path;

	j = 0;
	execve(pipex->cmd[0], pipex->cmd, pipex->env);
	if (pipex->path != NULL)
	{
		if (ft_strncmp(pipex->cmd[0], "./", 2) == 0)
			bash_script(pipex);
		while (pipex->path[j])
		{
			full_path = ft_strsjoin(pipex->path[j], pipex->cmd[0], '/');
			execve(full_path, pipex->cmd, pipex->env);
			free(full_path);
			j++;
		}
	}
	g_err_no = 127;
	ft_putstr_fd(pipex->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(g_err_no);
}

void	mid(t_pipex *pipex, t_data *data_base)
{
	int	fders[2];

	if (pipe(fders) == -1)
	{
		g_err_no = 1;
		ft_putstr_fd("Error forking\n", 2);
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
		close(fders[0]);
		dup2(pipex->fds[0], STDIN_FILENO);
		dup2(fders[1], STDOUT_FILENO);
		close(pipex->fds[0]);
		close(fders[1]);
		if (is_builtin(pipex->cmd[0]))
		{
			execute_builtin(pipex->cmd, data_base);
			exit(g_err_no);
		}
		else
			execute_cmd(pipex);
	}
	pipex->forks++;
	close(pipex->fds[0]);
	close(fders[1]);
	pipex->fds[0] = fders[0];
}

void	first(t_pipex *pipex, t_data *data_base)
{
	if (pipe(pipex->fds) == -1)
	{
		g_err_no = 1;
		ft_putstr_fd("Error pipeing\n", 2);
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
		close(pipex->fds[0]);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->fds[1], STDOUT_FILENO);
		if (pipex->infile != 0)
			close(pipex->infile);
		close(pipex->fds[1]);
		if (is_builtin(pipex->cmd[0]))
		{
			execute_builtin(pipex->cmd, data_base);
			exit(g_err_no);
		}
		else
			execute_cmd(pipex);
	}
	pipex->forks++;
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
		dup2(pipex->fds[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->fds[0]);
		if (pipex->outfile != 1)
			close(pipex->outfile);
		if (is_builtin(pipex->cmd[0]))
		{
			execute_builtin(pipex->cmd, data_base);
			exit(g_err_no);
		}
		else
			execute_cmd(pipex);
	}
	pipex->forks++;
	close(pipex->fds[0]);
	if (pipex->outfile != 1)
		close(pipex->outfile);
}
