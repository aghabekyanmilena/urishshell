/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:39:27 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/01 18:59:31 by miaghabe         ###   ########.fr       */
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
	pipex->current_cmd = 0;
	pipex->env = db->env;
	pipex->pid = (int *)malloc(pipex->count_cmd * sizeof(int));
	// check_files(argv[1], argv[argc - 1], pipex);
	// pipex->infile = open(argv[1], O_RDONLY);
	// pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (pipex->infile == -1 || pipex->outfile == -1)
	// 	err_exit("Error opening\n", pipex, 1);
}
