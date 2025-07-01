/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:39:35 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/01 18:56:48 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "tokenization.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "built_in.h"

# define TMP_FILE "/tmp/heredoc.tmp"

typedef struct s_pipex
{
	int				fds[2];
	int				*pid;
	char			**path;
	char			**env;
	int				infile;
	int				outfile;
	char			*limiter;
	char			**cmd;
	int				current_cmd;
	int				count_cmd;
}					t_pipex;

void	pipex_start(t_data *db, t_token *token);
void	init(t_data *db, t_pipex *pipex);
void	read_here_doc(t_pipex *heredoc, char *limiter);
void	check_files(char *infile, char *outfile, t_pipex *pipex);
void	err_exit(char *message, t_pipex *pipex, int k);
void	free_double(char **s);
void	first(t_pipex *pipex, t_data *data_base);
void	last(t_pipex *pipex, t_data *data_base);
void	mid(t_pipex *pipex, t_data *data_base);
void	execute_cmd(t_pipex *pipex);
char	*ft_join(char *s1, char *s2, char ch);

#endif