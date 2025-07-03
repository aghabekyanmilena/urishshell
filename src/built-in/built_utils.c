/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:46:33 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 15:07:03 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"));
}

int	execute_builtin(char **args, t_data *data)
{
	if (!args[0])
		return (1);
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(args, data));
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd(data));
	if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(args));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args, data));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args, data));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(data));
	return (1);
}
