/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:13:15 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 21:34:51 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sort_env(char **env)
{
	int		i;
	char	*tmp;
	int		len;
	int		counter;

	len = 0;
	counter = 0;
	while (env[len])
		len++;
	while (counter < len)
	{
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		counter++;
	}
}
