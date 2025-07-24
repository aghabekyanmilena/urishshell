/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:56 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/24 18:03:07 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_lim(t_limiter **cmd)
{
	t_limiter	*tmp;
	t_limiter	*next;

	if (!cmd || !*cmd)
		return ;
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

void	free_cmd(t_token **cmd)
{
	t_token	*tmp;
	t_token	*next;

	if (!cmd || !*cmd)
		return ;
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

void	free_struct(t_pipex *pipex)
{
	if (!pipex)
		return ;
	free_double(pipex->path);
	free(pipex->pid);
}

void	init(t_data *db, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd = NULL;
	pipex->limiter = NULL;
	pipex->path = NULL;
	pipex->heredoc = 0;
	while (db->env[i])
	{
		if (ft_strncmp(db->env[i], "PATH=", 5) == 0)
			pipex->path = ft_split(db->env[i] + 5, ':');
		i++;
	}
	pipex->count_cmd = db->pipes_count + 1;
	pipex->env = db->env;
	pipex->current_cmd = 0;
	pipex->forks = 0;
	pipex->pid = (int *)ft_calloc(pipex->count_cmd, sizeof(int));
	if (!(pipex->pid))
		return ;
	db->pipex = pipex;
	get_lim(db->token, pipex);
}

void	free_double(char **s)
{
	int	i;

	i = 0;
	if (!s || !(*s))
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
	s = NULL;
}
