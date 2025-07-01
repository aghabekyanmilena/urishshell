/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:56 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/01 22:58:51 by anush            ###   ########.fr       */
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

char	*ft_join(char *s1, char *s2, char ch)
{
	char	*s;
	int		l1;
	int		l2;
	int		i;

	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	s = (char *)malloc((l1 + l2 + 2) * sizeof(char));
	if (!s)
		return (NULL);
	while (i < l1)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = ch;
	i = 0;
	while (i < l2)
	{
		s[l1 + i + 1] = s2[i];
		i++;
	}
	s[l1 + l2 + 1] = '\0';
	return (s);
}

void	free_double(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	err_exit(char *message, t_pipex *pipex, int k)
{
	ft_putstr_fd(message, 2);
	free_double(pipex->cmd);
	free(pipex->pid);
	free_double(pipex->path);
	exit(k);
}

// void	check_files(char *infile, char *outfile, t_pipex *pipex)
// {
// 	char	*m;

// 	if (access(infile, F_OK) == -1)
// 	{
// 		m = ft_strjoin((pipex->argv)[1], ": no such file or directory");
// 		ft_putstr_fd(m, 2);
// 		free(m);
// 		err_exit("\n", pipex, 0);
// 	}
// 	if (access(infile, R_OK) == -1)
// 	{
// 		m = ft_strjoin((pipex->argv)[1], ": permission denied");
// 		ft_putstr_fd(m, 2);
// 		free(m);
// 		err_exit("\n", pipex, 0);
// 	}
// 	else if (access(outfile, F_OK) != -1 && access(outfile, W_OK) == -1)
// 	{
// 		m = ft_strjoin((pipex->argv)[pipex->argc - 1], ": permission denied");
// 		ft_putstr_fd(m, 2);
// 		free(m);
// 		err_exit("\n", pipex, 1);
// 	}
// }
