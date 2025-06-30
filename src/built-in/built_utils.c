/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:46:33 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/30 15:41:38 by miaghabe         ###   ########.fr       */
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
		// || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"));
}

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->args[0])
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (builtin_cd(cmd->args, data));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (builtin_exit(cmd->args));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (builtin_export(cmd->args, data));
	// if (!ft_strcmp(cmd->args[0], "unset"))
		// return (builtin_unset(cmd->args, data));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (builtin_env(data));
	return (1);
}
