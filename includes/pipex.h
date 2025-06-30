/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:39:35 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/30 13:41:52 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "tokenization.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define TMP_FILE "/tmp/heredoc.tmp"

typedef struct s_pipex
{
	int				fds[2];
	int				*pid;
	char			**path;
	// char			**argv;
	// int				argc;
	char			**env;
	int				infile;
	int				outfile;
	char			**cmd;
	int				current_cmd;
	int				count_cmd;
}					t_pipex;

// void	pipex_start(t_data *db, t_token *token);
void	init(t_data *db, t_pipex *pipex);
void	check_files(char *infile, char *outfile, t_pipex *pipex);
void	err_exit(char *message, t_pipex *pipex, int k);
void	free_double(char **s);
void	first(t_pipex *pipex);
void	last(t_pipex *pipex);
void	mid(t_pipex *pipex);
void	execute_cmd(t_pipex *pipex);
void	here_doc(int argc, char **argv, char **env, t_pipex *heredoc);
int		ft_strcmp_for_limiter(char *s1, char *s2);
char	*ft_join(char *s1, char *s2, char ch);

#endif