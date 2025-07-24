/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:14:20 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/24 17:54:07 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	whilei_mejiny(t_limiter *cpy, t_pipex *pipex, t_data *db, char *lim)
{
	char	*str;
	char	*line;
	char	*new;

	new = NULL;
	write(1, "> ", 2);
	str = get_next_line(0);
	db->command_count++;
	if (!str || ft_strcmp(lim, str) == 0)
	{
		if (!str)
		{
			write(1, "\nwarning: here-document at line ", 33);
			line = ft_itoa(db->command_count);
			write(1, line, ft_strlen(line));
			free(line);
			write(1, " delimited by end-of-file (wanted `", 36);
			write(1, cpy->value, ft_strlen(cpy->value));
			write(1, "')\n", 3);
		}
		return (free(str), 1);
	}
	new = dollar_in_line(str, db);
	write(pipex->infile, new, ft_strlen(new));
	return (free(new), free(str), 0);
}

void	read_here_doc(t_pipex *pipex, t_limiter *cpy, t_data *db)
{
	char		*lim;

	while (cpy)
	{
		lim = ft_strjoin(cpy->value, "\n");
		if (pipex->infile != 0)
			close (pipex->infile);
		pipex->infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		while (1)
		{
			if (whilei_mejiny(cpy, pipex, db, lim))
				break ;
		}
		free(lim);
		close(pipex->infile);
		pipex->infile = open(TMP_FILE, O_RDONLY);
		unlink(TMP_FILE);
		cpy = cpy->next;
	}
}

int	waiting_heredoc(pid_t pid)
{
	int	status;
	int	count;

	count = 0;
	waitpid(pid, &status, 0);
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
	return (count);
}

int	heredoc(t_pipex *pipex, t_limiter *cpy, t_data *db)
{
	pid_t	pid;
	int		count;

	count = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		read_here_doc(pipex, cpy, db);
		exit(0);
	}
	count = waiting_heredoc(pid);
	pipex->heredoc = 1;
	return (count);
}

void	commands(t_token *cpy, t_pipex *pipex, t_data *db)
{
	pipex->infile = 0;
	pipex->outfile = 1;
	while (cpy)
	{
		if (cpy->type == INFILE && !check_infile(cpy, pipex, db))
			return ;
		else if ((cpy->type == OUTFILE || cpy->type == OUTFILE_APPEND)
			&& !check_outfile(cpy, pipex, db))
			return ;
		cpy = cpy->next;
	}
}
