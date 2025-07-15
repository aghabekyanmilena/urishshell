/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:48:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/15 17:22:09 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

int builtin_cd(char **args, t_data *data)
{
	char	*dir;
	char	*tmp;
	char	*oldpwd;
	char	*cwd;
	int		i;

	i = 0;
	dir = NULL;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_err_no = 1;
		return (1);
	}
	if (!args[1] || ft_strcmp(args[1], "-") == 0 || ft_strcmp(args[1], "~") == 0)
		dir = ft_strdup(get_env(data->env, "HOME"));
	else if (ft_strncmp(args[1], "~/", 2) == 0)
	{
		tmp = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
		dir = get_env(data->env, "HOME");
		dir = ft_strjoin(dir, tmp);
		free(tmp);
	}
	else
		dir = ft_strdup(args[1]);
	if (!dir)
	{
		ft_putendl_fd("cd: HOME not set\n", 2);
		g_err_no = 1;
		free(dir);
		return (1);
	}
	oldpwd = get_env(data->env, "PWD");
	if (oldpwd)
		update_env(data, "OLDPWD", oldpwd);
	if (chdir(dir) != 0)
	{
		g_err_no = 1;
		free(dir);
		perror("cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env(data, "PWD", cwd);
		free(cwd);
	}
	g_err_no = 0;
	free(dir);
	return (0);
}
