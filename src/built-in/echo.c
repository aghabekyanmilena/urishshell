/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:17:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/03 20:09:53 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

int	builtin_echo(char **args)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		char	*str;
		// size_t	len = ft_strlen(args[i]);
		str = ft_strdup(args[i]);
		if (str)
		{
			printf("%s", str);
			free(str);
		}
		// if (args[i + 1])
		// 	printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
