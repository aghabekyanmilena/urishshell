/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:48:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/05 18:32:24 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

char *get_env(char **env, const char *key);
void update_env(t_data *data, const char *key, const char *value);

int builtin_cd(char **args, t_data *data)
{
	char	*dir;
	char	*oldpwd;
	char	*cwd;

	if (args[1])
		dir = args[1];
	else
		dir = get_env(data->env, "HOME");
	if (!dir)
	{
		ft_putendl_fd("cd: HOME not set\n", 17);
		return (1);
	}
	oldpwd = get_env(data->env, "PWD");
	if (oldpwd)
		update_env(data, "OLDPWD", oldpwd);
	if (chdir(dir) != 0)
	{
		perror("cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env(data, "PWD", cwd);
		free(cwd);
	}
	return (0);
}
