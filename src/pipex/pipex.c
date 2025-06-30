/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:39:27 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/30 12:24:57 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init(t_data *db, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd = NULL;
	pipex->path = NULL;
	while (db->env[i])
	{
		if (ft_strncmp(db->env[i], "PATH=", 5) == 0)
			pipex->path = ft_split(db->env[i] + 5, ':');
		i++;
	}
	// pipex->argc = argc;
	pipex->count_cmd = db->pipes_count + 1;
	pipex->current_cmd = 0;
	// pipex->argv = argv;
	pipex->env = db->env;
	pipex->pid = (int *)malloc(pipex->count_cmd * sizeof(int));
	// check_files(argv[1], argv[argc - 1], pipex);
	// pipex->infile = open(argv[1], O_RDONLY);
	// pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (pipex->infile == -1 || pipex->outfile == -1)
	// 	err_exit("Error opening\n", pipex, 1);
}

// void	pipex_start(int argc, char **argv, char **env, t_pipex *pipex)
// {
// 	int		status;
// 	int		i;

// 	init(argc, argv, env, pipex);
// 	while (pipex->current_cmd < pipex->count_cmd)
// 	{
// 		pipex->cmd = ft_split((pipex->argv)[pipex->current_cmd + 2], ' ');
// 		if (pipex->cmd == NULL)
// 			err_exit("Command is empty\n", pipex, 1);
// 		if (pipex->current_cmd == 0)
// 			first(pipex);
// 		else if (pipex->current_cmd == pipex->count_cmd - 1)
// 			last(pipex);
// 		else
// 			mid(pipex);
// 		free_double(pipex->cmd);
// 		(pipex->current_cmd)++;
// 	}
// 	i = 0;
// 	while (i < pipex->count_cmd)
// 		waitpid(pipex->pid[i++], &status, 0);
// 	free_double(pipex->path);
// 	free(pipex->pid);
// }



// int	main(int argc, char **argv, char **env)
// {
// 	t_pipex	pipex;
// 	t_pipex	heredoc;

// 	if (argc < 5)
// 		return (write(2, "Wrong number of arguments\n", 26), 1);
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
// 		here_doc(argc, argv, env, &heredoc);
// 	else
// 		pipex_start(argc, argv, env, &pipex);
// 	return (0);
// }
