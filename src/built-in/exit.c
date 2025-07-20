/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:23:09 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/20 15:00:43 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	tiva(char *argument)
{
	int	i;

	i = 0;
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

static void	check_arg(char **args)
{
	if (args[1] && tiva(args[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
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
	check_arg(args);
	if (count > 2)
		return (ft_putendl_fd("exit: too many arguments", 2), g_err_no = 1, 1);
	if (args[1])
	{
		if (!ft_atolli_safe(args[1], &exit_code, 1))
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
