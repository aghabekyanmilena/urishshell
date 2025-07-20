/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:23:09 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/20 14:02:29 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	ft_atolli_safe(const char *str, long long *out)
{
	int				sign = 1;
	unsigned long	result = 0;
	int				i = 0;

	*out = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807ULL && !(sign == -1 && result == 9223372036854775808ULL))
			return (0);
		i++;
	}
	if (sign == -1 && result == 9223372036854775808ULL)
		*out = -9223372036854775807LL - 1;
	else
		*out = result * sign;
	return (1);
}

static int	tiva(char *argument)
{
	int	i = 0;
	while (argument[i])
	{
		if (ft_isdigit(argument[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_before_exit(t_data *db, char **args)
{
	free_double(args);
	free_struct(db->pipex);
	free_tokens(db);
	free_double(db->env);
	rl_clear_history();
}

int	builtin_exit(char **args, t_data *db)
{
	long long	exit_code;
	int			count;

	exit_code = g_err_no;
	printf("exit\n");
	count = 0;
	while (args[count])
		count++;
	if (args[1] && tiva(args[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (count > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_err_no = 1;
		return (1);
	}
	if (args[1])
	{
		if (!ft_atolli_safe(args[1], &exit_code))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_before_exit(db, args);
			exit(2);
		}
		free_before_exit(db, args);
		exit((unsigned char)exit_code);
	}
	free_before_exit(db, args);
	exit((unsigned char)exit_code);
}
