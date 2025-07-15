/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:02:40 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/15 17:22:26 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include "tokenization.h"

typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_command	t_cmd;
typedef struct s_pipex		t_pipex;
typedef struct s_limiter	t_limiter;

// utils
bool	is_builtin(char *cmd);
int		execute_builtin(char **args, t_data *data);

// echo
int		builtin_echo(char **args);

// exit
int	builtin_exit(char **args, t_data *db);

// env
// int		builtin_env(t_data *data);
int	builtin_env(char **args, t_data *data);

// cd
int		builtin_cd(char **args, t_data *data);

// pwd
int		builtin_pwd(t_data *data);

// export
int		builtin_export(char **args, t_data *data);
int		find_env_var_index(char **env, char *name);

// unset
int		builtin_unset(char **args, t_data *data);

char	*get_env(char **env, const char *key);
void	update_env(t_data *data, char *key, const char *value);

#endif