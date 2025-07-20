/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:39:35 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/20 16:46:16 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "tokenization.h"
# include "get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "built_in.h"
# include "signals.h"

# define TMP_FILE "/tmp/here_doc.tmp"

typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_command	t_cmd;
typedef struct s_limiter	t_limiter;

typedef struct s_limiter
{
	char			*value;
	t_limiter		*next;
}					t_limiter;

typedef struct s_pipex
{
	int				fds[2];
	int				*pid;
	char			**path;
	char			**env;
	int				infile;
	int				outfile;
	t_limiter		*limiter;
	char			**cmd;
	int				current_cmd;
	int				count_cmd;
	int				forks;
}					t_pipex;

void	pipex_start(t_data *db, t_token *cpy, t_token *cmd);
void	read_here_doc(t_pipex *heredoc, t_limiter *limiter, t_data *db);
void	first(t_pipex *pipex, t_data *data_base);
void	last(t_pipex *pipex, t_data *data_base);
void	mid(t_pipex *pipex, t_data *data_base, int fders[2]);
void	no_pipe(t_pipex *pipex, t_data *data_base);
void	execute_cmd(t_pipex *pipex);
void	bash_script(t_pipex *pipex);
char	*dollar_in_line(char *line, t_data *db);

//files
void	commands(t_token *cmd, t_pipex *pipex, t_data *db);
void	closing_files(t_pipex *pipex);
void	err_for_files(char *value, char *mess, t_data *db);

//utils
void	init(t_data *db, t_pipex *pipex);
void	free_struct(t_pipex *pipex);
void	free_cmd(t_token **cmd);
void	free_double(char **s);
void	free_lim(t_limiter **cmd);

#endif