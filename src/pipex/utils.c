/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:56 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/07 15:29:18 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init(t_data *db, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd = NULL;
	pipex->limiter = NULL;
	pipex->path = NULL;
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
}
void	free_double(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

