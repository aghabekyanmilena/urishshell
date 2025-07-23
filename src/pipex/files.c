/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:32:36 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/20 18:40:26 by atseruny         ###   ########.fr       */
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

void	err_for_files(char *value, char *mess, t_data *db)
{
	ft_putstr_fd(value, 2);
	ft_putstr_fd(mess, 2);
	db->for_syntax_err = 1;
	g_err_no = 1;
}

int	check_infile(t_token *cpy, t_pipex *pipex, t_data *db)
{
	if (access(cpy->value, F_OK) == -1)
		return (err_for_files(cpy->value, ": No such file or directory\n",
				db), 0);
	else if (access(cpy->value, R_OK) == -1)
		return (err_for_files(cpy->value, ": Permission denied\n", db), 0);
	pipex->infile = open(cpy->value, O_RDONLY);
	if (pipex->infile == -1)
		return (err_for_files(cpy->value, ": No such file or directory\n",
				db), 0);
	return (1);
}

int	check_outfile(t_token *cpy, t_pipex *pipex, t_data *db)
{
	if (access(cpy->value, F_OK) != -1
		&& access(cpy->value, W_OK) == -1)
		return (err_for_files(cpy->value, ": Permission denied\n", db), 0);
	if (cpy->type == OUTFILE_APPEND)
		pipex->outfile = open(cpy->value, O_WRONLY
				| O_CREAT | O_APPEND, 0777);
	else
		pipex->outfile = open(cpy->value, O_WRONLY
				| O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile == -1)
		return (err_for_files(cpy->value, ": No such file or directory\n",
				db), 0);
	return (1);
}
