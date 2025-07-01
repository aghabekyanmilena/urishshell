/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:27:03 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/29 14:49:26 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

int	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
