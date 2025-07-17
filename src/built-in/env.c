/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:27:03 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 16:23:12 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	havasar_chka(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_env(char **args, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (args[j])
		j++;
	if (j > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		g_err_no = 1;
		return (1);
	}
	i = 0;
	while (data->env && data->env[i])
	{
		if (havasar_chka(data->env[i]) == 0)
		{
			i++;
			continue ;
		}
		printf("%s\n", data->env[i]);
		i++;
	}
	g_err_no = 0;
	return (0);
}
