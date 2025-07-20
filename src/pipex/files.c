/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:32:36 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/19 19:01:22 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	closing_files(t_pipex *pipex)
{
	if (pipex->infile != 0)
		close(pipex->infile);
	if (pipex->outfile != 1)
		close(pipex->outfile);
}

void	add_lim(t_limiter **head, char *value)
{
	t_limiter	*new;
	t_limiter	*tmp;

	new = malloc(sizeof(t_limiter));
	new->value = value;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	err_for_files(char *value, char *mess)
{
	ft_putstr_fd(value, 2);
	ft_putstr_fd(mess, 2);
	g_err_no = 1;
}

int	check_infile(t_token *cpy, t_pipex *pipex)
{
	if (access(cpy->value, F_OK) == -1)
		return (err_for_files(cpy->value, ": No such file or directory\n"), 0);
	else if (access(cpy->value, R_OK) == -1)
		return (err_for_files(cpy->value, ": Permission denied\n"), 0);
	pipex->infile = open(cpy->value, O_RDONLY);
	if (pipex->infile == -1)
		return (err_for_files(cpy->value, ": No such file or directory\n"), 0);
	return (1);
}

void	commands(t_token *cpy, t_pipex *pipex)
{
	pipex->infile = 0;
	pipex->outfile = 1;
	while (cpy)
	{
		if (cpy->type == INFILE && !check_infile(cpy, pipex))
			return ;
		else if (cpy->type == OUTFILE || cpy->type == OUTFILE_APPEND)
		{
			if (access(cpy->value, F_OK) != -1
				&& access(cpy->value, W_OK) == -1)
			{
				err_for_files(cpy->value, ": Permission denied\n");
				return ;
			}
			if (cpy->type == OUTFILE_APPEND)
				pipex->outfile = open(cpy->value, O_WRONLY
						| O_CREAT | O_APPEND, 0777);
			else
				pipex->outfile = open(cpy->value, O_WRONLY
						| O_CREAT | O_TRUNC, 0777);
		}
		else if (cpy->type == LIMITER)
			add_lim(&pipex->limiter, ft_strdup(cpy->value));
		cpy = cpy->next;
	}
}
