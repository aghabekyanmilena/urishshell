/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:23:09 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/05 21:21:38 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int	exit_code;
	int	i;
	
	exit_code = 0;
	printf("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		printf("A\n");
	if (args[1])
	{
		if (!is_digital(args[1]))
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_code = ft_atoi(args[1]);
	}
	exit(exit_code);
}
