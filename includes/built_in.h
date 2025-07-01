/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:02:40 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/01 15:32:23 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
#define BUILT_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "tokenization.h"

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	int		pipe_in;
	int		pipe_out;
	struct s_cmd *next;
}	t_cmd;

// utils
bool	is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_data *data);

// echo
int		builtin_echo(char **args);

// exit
int		builtin_exit(char **args);

// env
int		builtin_env(t_data *data);

// cd
int		builtin_cd(char **args, t_data *data);

// pwd
int		builtin_pwd(void);

// export
int builtin_export(char **args, t_data *data);
int	find_env_var_index(char **env, const char *name);

// unset
int	builtin_unset(char **args, t_data *data);

#endif