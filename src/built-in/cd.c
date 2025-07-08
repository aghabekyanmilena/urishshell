/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:48:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 14:50:14 by atseruny         ###   ########.fr       */
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
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		ERR_NO = 1;
		return (1);
	}
	if (args[1])
		dir = args[1];
	else
		dir = get_env(data->env, "HOME");
	if (!dir)
	{
		ft_putendl_fd("cd: HOME not set\n", 2);
		ERR_NO = 1;
		return (1);
	}
	oldpwd = get_env(data->env, "PWD");
	if (oldpwd)
		update_env(data, "OLDPWD", oldpwd);
	if (chdir(dir) != 0)
	{
		ERR_NO = 1;
		perror("cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env(data, "PWD", cwd);
		free(cwd);
	}
	ERR_NO = 0;
	return (0);
}
