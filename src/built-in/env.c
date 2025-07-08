/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:27:03 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 14:14:57 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

int	builtin_env(char **args, t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (args[j])
		j++;
	if (j > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		ERR_NO = 1;
		return (1);
	}
	i = 0;
	while (data->env && data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	ERR_NO = 0;
	return (0);
}
