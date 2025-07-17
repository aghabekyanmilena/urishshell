/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:46:33 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 17:12:24 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	skip_whitespace_and_sign(const char *str, int *sign, int *i)
{
	*i = 0;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!str[*i])
		return (0);
	return (1);
}

static int	is_overflow(unsigned long result, int sign)
{
	if (result > 9223372036854775807ULL
		&& !(sign == -1 && result == 9223372036854775808ULL))
		return (1);
	return (0);
}

int	ft_atolli_safe(const char *str, long long *out, int sign)
{
	unsigned long	result;
	int				i;

	result = 0;
	*out = 0;
	if (!skip_whitespace_and_sign(str, &sign, &i))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (is_overflow(result, sign))
			return (0);
		i++;
	}
	if (sign == -1 && result == 9223372036854775808ULL)
		*out = LLONG_MIN;
	else
		*out = result * sign;
	return (1);
}

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
		return (builtin_echo(args, 0));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd(data));
	if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(args, data));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args, data));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args, data));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(args, data));
	return (1);
}
