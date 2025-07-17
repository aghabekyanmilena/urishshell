/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:48:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 17:26:47 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static char	*get_cd_target(char **args, t_data *data)
{
	char	*dir;
	char	*tmp;

	if (!args[1] || ft_strcmp(args[1], "-") == 0
		|| ft_strcmp(args[1], "~") == 0)
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
		ft_putendl_fd("cd: HOME not set", 2);
		g_err_no = 1;
	}
	return (dir);
}

int	builtin_cd(char **args, t_data *data)
{
	char	*dir;
	char	*oldpwd;
	char	*cwd;
	int		arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), g_err_no = 1, 1);
	dir = get_cd_target(args, data);
	if (!dir)
		return (1);
	oldpwd = get_env(data->env, "PWD");
	if (oldpwd)
		update_env(data, "OLDPWD", oldpwd);
	if (chdir(dir) != 0)
		return (perror("cd"), free(dir), g_err_no = 1, 1);
	cwd = getcwd(NULL, 0);
	if (cwd)
		update_env(data, "PWD", cwd);
	free(cwd);
	free(dir);
	g_err_no = 0;
	return (0);
}
